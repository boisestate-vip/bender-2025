
/* main file for the bender process daemon node */

#include "communication.h"
#include "util.h"
#include "gost.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <systemd/sd-daemon.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include <arpa/inet.h>

int main(int argc, char ** argv) {

   /* get the port to listen on */
   int port = BENDER_DEFAULT_PORT;

   char * buf;
   int len = load("/etc/bender/daemon.conf",&buf);

   if (len == -1) {
      fprintf(stderr,"<4>unable to locate config file, using default port %d\n",port);
   }
   else {
      char * loc = strstr(buf,"socket=");
      if (loc) 
         loc = strstr(loc,"=") + 1;
      if (!loc) 
         fprintf(stderr,"<4>unable to parse port number for config file, using default port %d\n",port);
      else
         port = atoi(loc);

      free(buf);
   }

   int encrypt_on = 0;

   gost_key key;
   struct gost_opt gost_opts;
   gost_opts.mode = GOSTM_CF;
   gost_opts.key = &key;
   gost_opts.s_box = &gost_default_s_box;

   if (gost_loadkey("/etc/bender/key",&key) == 0)
      encrypt_on = 1;
   else
      fprintf(stderr,"<3>unable to locate key file, proceeding with encryption off\n");


   int daemon_mode = 1;
   int fd = -1;
   int out_fd = -1;

   if (argc != 4) {
      /* the incorrect number of arguments has been passed
       * to the daemon on startup. There is some sort of 
       * error in the daemon configuration if this happens */
      fprintf(stderr,"<3>incorrect number of arguments passed (%d). failing\n",argc);
      fprintf(stdout,"usage: %s [ros_version (iron, ...)] [bender_systemname]" 
                     " [bender_dirpath] [-D (to run daemon as process]\n",argv[0]);

      sd_notify(0,"STATUS=incorrect number of arguments passed\n"
                  "ERRNO=1\n"
                  "EXIT_STATUS=1");

      exit(EPERM);
   }

   fprintf(stderr,"ros version: %s\n",argv[1]);
   fprintf(stderr,"bender name: %s\n",argv[2]);
   fprintf(stderr,"bender path: %s\n",argv[3]);

   struct bender_exec_metadata metadata;
   metadata.ros_version = argv[1];
   metadata.bender_name = argv[2];
   metadata.bender_path = argv[3];
   int res;

   if (chdir(metadata.bender_path) == -1) {
      fprintf(stderr,"<3>bad bender directory passed. failing\n");

      sd_notify(0,"STATUS=bad bender directory passed.\n"
                  "ERRNO=2\n"
                  "EXIT_STATUS=2\n");

      exit(ENOENT);
   }

   fd = socket(AF_INET, SOCK_DGRAM, 0);
   if (fd == -1) {
      perror("socket");
      exit(errno);
   }

   struct sockaddr_in addr;
   socklen_t addr_len = sizeof(addr);
   bzero(&addr,addr_len);

   addr.sin_port = htons(port);
   addr.sin_family = AF_INET;
   addr.sin_addr.s_addr = htonl(INADDR_ANY);

   res = bind(fd,(struct sockaddr *)&addr,addr_len);
   if (res == -1) {
      perror("bind");
      exit(errno);
   }

   fprintf(stdout,"listening on port %d\n",port);

   if (fd == -1) {
      /* no descriptor that meets the expected values is set */
      fprintf(stderr,"<3>no file descriptor found that meets the requirements. failing\n");

      sd_notify(0,"STATUS=no file descriptor meeting requirements found\n"
                  "ERRNO=9\n"
                  "EXIT_STATUS=9");

      exit(EBADF);
   }

   struct bender_exec_list * exec = NULL;
   res = bender_generate_exec_list("/etc/bender/cmd.conf",&exec,&metadata,0);

   if (res == -1) {
      /* there must be some error in our config file */
      fprintf(stderr,"<3>command configuration file has errors. failing\n");

      sd_notify(0,"STATUS=command configuration file has errors\n"
                  "ERRNO=71\n"
                  "EXIT_STATUS=71");

      exit(EPROTO);
   }

   sd_pid_notify_with_fds(0, 0, "FDSTORE=1", &fd, 1);

   sd_notify(0,"READY=1");

   sd_notify_barrier(0, 5 * 1000000);

   /* now we are in the full system processing state */

   int msg_len;
   fd_set read_set;
   struct bender_communication message;
   bzero(&message,sizeof(message));


   for ( ; ; ) {

      FD_ZERO(&read_set);
      FD_SET(fd,&read_set);

      res = select(fd+1,&read_set,NULL,NULL,NULL);

      if (res == -1) {
         /* we are just going to ignore this one */
         fprintf(stderr,"<4>select returned an error: %d\n",errno);
         errno = 0;
         continue;
      }

      if (FD_ISSET(fd,&read_set)) {

         struct sockaddr_in src_addr;
         socklen_t src_addr_len = sizeof(src_addr);
         bzero(&src_addr,src_addr_len);

         msg_len = recvfrom(fd,&message,sizeof(message),0,(struct sockaddr *)&src_addr,&src_addr_len);

         if (msg_len == -1) {
            /* the incoming message failed for some reason */
            fprintf(stderr,"<4>recvfrom returned an error: %d\n",errno);
            errno = 0;
            continue;
         }

         gost_opts.initialization_const = message.nonce;
         if (encrypt_on && 0 == bender_decrypt_message(&message,&gost_opts)) {
            fprintf(stderr,"<4>message decryption failed, discarding\n");
            errno = 0;
            continue;
         }
         else if (!encrypt_on && message.msg_type & BENDER_ENCRYPTED) {
            fprintf(stderr,"<4>message is encrypted, discarding\n");
            errno = 0;
            continue;
         }

         /* check if message is directed to us */
         if (message.system_name[0] != '*' && strcmp(message.system_name,metadata.bender_name))
            continue;

         if (message.msg_type == BENDERC_RESTART) {
            sd_notify(0,"RELOADING=1");

            fprintf(stderr,"<6>reloading configuration file\n");

            /* perform reloading operations */
            struct bender_exec_list * new_exec = NULL;
            res = bender_generate_exec_list("/etc/bender/cmd.conf",&new_exec,&metadata,0);

            if (res == -1) {
               fprintf(stderr,"<4>new configuration file has errors, keeping old one: %d\n",errno);
            }
            else {
               bender_degenerate_exec_list(&exec);
               exec = new_exec;
            }

            fprintf(stderr,"<6>reloading key file\n");

            gost_key new_key;
            res = gost_loadkey("/etc/bender/key",&new_key);

            if (res == -1) {
               fprintf(stderr,"<4>unable to load new key file, keeping old settings (errno: %d)\n",errno);
            }
            else {
               memcpy(key,new_key,sizeof(gost_key));
               encrypt_on = 1;
            }

            sd_notify(0,"READY=1");

         }
         else if (message.msg_type == BENDERC_INTERNAL) {
         }
         else {
            res = bender_process_message(&message,&msg_len,&metadata,exec);

            if (res == -1) {
               /* some call or action in the message processing has returned an error */
               fprintf(stderr,"<4>bender_process_message returned an error: %d\n",errno);
               errno = 0;
               //continue; /* send the return message anyway */
            }

            fprintf(stderr,"<5>response message: %s\n",message.message);

            if (encrypt_on)
               bender_encrypt_message(&message,&gost_opts);

            fprintf(stderr,"<4>Target port: %d\n",ntohs(src_addr.sin_port));
            char buf[128];
            inet_ntop(AF_INET,&src_addr,buf,src_addr_len);
            fprintf(stderr,"<4>Target ip addr: %s\n",buf);
            res = sendto(fd,&message,bender_commsize(&message),0,(struct sockaddr *)&src_addr,src_addr_len);

            if (res == -1) {
               /* some call or action in the message processing has returned an error */
               fprintf(stderr,"<4>sendto returned an error: %d\n",errno);
               errno = 0;
               continue;
            }
         }
      }
   }

   return 0;
}
