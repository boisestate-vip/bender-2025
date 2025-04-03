
#include "communication.h"
#include "util.h"
#include "gost.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>
#include <errno.h>
#include <signal.h>
#include <time.h>

#include <sys/select.h>
#include <netinet/in.h>
#include <netinet/ip.h>

/* needed as global for the signal handler */
int continue_wait = 1;

void bender_interrupt_handler(int sig) {
   continue_wait = 0;
}

int main(int argc, char ** argv) {

   char * help_message = 
      "BENDER PROCESS TOOL\n"
      "-----------------------------------------------------------------------"
      "------------------------------------\n"
      "Used for managing and viewing the state of the bender robot. Commands\n"
      "can be sent, and results are returned for all systems online and\n" 
      "accesable via udp broadcast.\n"
      "\033[31mBe warned! This sytems is very insecure and should not be\n"
      "used in any way shape or form on an untrusted system\033[0m\n"
      "Options:\n"
      "\t-h\t\t | help:\tPrint this message. This is the default\n"
      "\t-v\t\t | version:\tPrint the tool version\n"
      "\t-r\t\t | restart:\tRestart all reachable daemons\n"
      "\t-c [cmd]\t | command:\tSend the given command to all reachable daemons.\n"
      "\t-d\t\t | debug:\tList all commands and mapping currently in the config file\n"
      "\t-C\t\t | check:\tCheck the command configuration file for errors\n"
      "\t-f [file]\t | file: set the configuration file to parse for commands. Default is /etc/bender/cmd.conf\n"
      "\t-n [name]\t | name:\tSend command to only a specific system. Name is controlled via $BENDER_HOSTNAME\n"
      "\t-p [port]\t | port:\tSend command to the given port as opposed to the default\n\n"
      "\t-k [key]\t | keypath:\tSet the path to the key to use for encryption. Default is /etc/bender/key\n";
   char * bender_path = "<bender-path>";
   char * bender_name = "<bender-name>";
   char * ros2_distro = "<ros2-distro>";
                           

   int c;
   char * name = "*";
   char * file = "/etc/bender/cmd.conf";
   char * keypath = "/etc/bender/key";
   char * message = NULL;
   int port = BENDER_DEFAULT_PORT;
   int reset = 0;
   int terminal = 0;
   int debug = 0;
   int check = 0;
   int encrypt_on = 0;

   int res, sock = socket(AF_INET,SOCK_DGRAM,0), one = 1;
   res = setsockopt(sock,SOL_SOCKET,SO_BROADCAST,&one,sizeof(one));
   if (res == -1) {
      fprintf(stderr,"failed setting socket to broadcast. exiting\n");
      exit(errno);
   }

   while ( (c = getopt(argc,argv, "hvrdc:Cn:p:f:k:") ) != -1) {

      switch (c) {

         case 'v':
            fprintf(stdout,"Bender Process Tool, V0.1.0\n");
            exit(0);
            break;

         case 'd':
            debug = 1;
            break;

         case 'r':
            reset = 1;
            break;

         case 'p':
            port = atoi(optarg);
            break;

         case 'f':
            file = optarg;
            break;

         case 'c':
            message = optarg;
            break;

         case 'C':
            check = 1;
            break;

         case 'n':
            name = optarg;
            break;

         case 'h':
            /* implicitly internally */
            break;

         case 'k':
            keypath = optarg;
            break;

         case '?':
            fprintf(stderr,"unknown argument format, exiting\n");
            exit(1);
            break;

         default:
            fprintf(stderr,"bad argument, exiting\n");
            exit(1);
            break;

      }

   }

   struct sockaddr_in addr;
   socklen_t addr_len = sizeof(addr);
   bzero(&addr,addr_len);
   addr.sin_family = AF_INET;
   addr.sin_port = htons(port);
   addr.sin_addr.s_addr = htonl(INADDR_ANY);

   struct bender_exec_list * exec = NULL;
   struct bender_exec_metadata unset;
   unset.ros_version = ros2_distro;
   unset.bender_name = bender_name;
   unset.bender_path = bender_path;


   uint64_t nonce;
   srandom(time(NULL)*clock());
   nonce = random();

   gost_key key;
   struct gost_opt gost_opts;
   gost_opts.mode = GOSTM_CF;
   gost_opts.key = &key;
   gost_opts.s_box = &gost_default_s_box;
   gost_opts.initialization_const = nonce;

   if (gost_loadkey(keypath,&key) == 0)
      encrypt_on = 1;
   else
      printf("no key found, passing messages unencrypted\n");

   errno = 0;

   if (check) {
      struct bender_exec_list * exec = NULL;
      struct bender_exec_metadata unset;
      bzero(&unset,sizeof(unset));
      res = bender_generate_exec_list(file,&exec,&unset,1);
      bender_degenerate_exec_list(&exec);

      if (res != -1)
         printf("\033[32mpassed\033[0m\n");

      exit(errno);
   }

   res = bender_generate_exec_list(file,&exec,&unset,0);

   if (debug) {

      struct bender_exec_list * curr = exec;
      while (curr != NULL) {
         fprintf(stdout,"[%d] %s = %s\n",curr->cmd_type,curr->external_cmd,curr->internal_cmd);
         curr = curr->next;

      }

      bender_degenerate_exec_list(&exec);
      exit(0);

   }

   if (reset) {

      struct bender_communication msg;
      bzero(&msg,sizeof(msg));
      msg.msg_type = BENDERC_RESTART;
      strncpy(msg.system_name,name,BENDER_SYSTEM_NAME_LEN-1);
      msg.system_name[BENDER_SYSTEM_NAME_LEN-1] = '\0';
      msg.message[0] = '\0';

      errno = 0;

      if (encrypt_on)
         bender_encrypt_message(&msg,&gost_opts);

      res = sendto(sock,&msg,bender_commsize(&msg),0,
                   (struct sockaddr *)&addr,addr_len);
      if (res == -1)
         fprintf(stderr,"error sending message\n");

      exit(errno);

   }
   else if (message) {

      res = strtrm(message);
      if (res == -1) {
         fprintf(stderr,"error parsing message\n");
         exit(errno);
      }

      struct bender_exec_list * curr = exec;
      while (curr != NULL) {

         if (bender_strmatch(curr->external_cmd,message,NULL))
            break;

         curr = curr->next;

      }
      if (curr == NULL) {
         fprintf(stderr,"unsupported operation sent\n");
         exit(1);
      }

      struct bender_communication msg;
      bzero(&msg,sizeof(msg));
      msg.msg_type = curr->cmd_type;
      strncpy(msg.system_name,name,BENDER_SYSTEM_NAME_LEN-1);
      msg.system_name[BENDER_SYSTEM_NAME_LEN-1] = '\0';
      strncpy(msg.message,message,BENDER_MESSAGE_LEN-1);
      msg.message[BENDER_MESSAGE_LEN-1] = '\0';

      if (encrypt_on)
         bender_encrypt_message(&msg,&gost_opts);

      errno = 0;

      res = sendto(sock,&msg,bender_commsize(&msg),0,
                   (struct sockaddr *)&addr,addr_len);
      if (res == -1)
         fprintf(stderr,"error sending message\n");


      goto waiton;

   }
   else {
      fprintf(stdout,"%s",help_message);
      exit(0);
   }

waiton:

   {
      struct sigaction action;
      bzero(&action,sizeof(action));

      action.sa_handler = bender_interrupt_handler;
      sigaction(SIGINT,&action,NULL);

      while (continue_wait) {

         struct bender_communication ret_msg;

         res = recvfrom(sock,&ret_msg,sizeof(ret_msg),0,(struct sockaddr *)&addr,&addr_len);

         /* ignore bad messages */
         if (res == -1) {
            fprintf(stderr,"error recieving message\n");
            continue;
         }

         if (encrypt_on && 0 == bender_decrypt_message(&ret_msg,&gost_opts)) {
            fprintf(stderr,"message decryption failed, discarding\n");
            continue;
         }
         else if (!encrypt_on && ret_msg.msg_type & BENDER_ENCRYPTED) {
            fprintf(stderr,"message is encrypted, discarding\n");
            continue;
         }

         /* ignore non-response messages */
         if (ret_msg.msg_type != BENDERC_RESPONSE)
            continue;

         fprintf(stdout,"\033[36mRESPONSE FROM %s :\033[0m\n%s\n",ret_msg.system_name,ret_msg.message);

      }

      fprintf(stdout,"i am sad you are leaving.... :(\n");

      bender_degenerate_exec_list(&exec);

      return 0;
   }

terminal:
   {

      return 0;
   }

   return 0;
}
