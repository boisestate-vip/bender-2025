
#include "communication.h"
#include "gost.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include <pthread.h>

struct benderd_thread_exec_info {
   int socket;
   struct bender_communication * msg;
   struct bender_exec_metadata * meta;
   struct bender_exec_list * exec;
   struct sockaddr * target;
};

void * benderd_thread_exec(void * in) {
   pthread_detach(pthread_self());

   struct benderd_thread_exec_info * info = (struct benderd_thread_exec_info *)in;

   int useless, res;
   res = bender_process_message(info->msg,&useless,info->meta,info->exec);

   if (res == -1) {
      /* some call or action in the message processing has returned an error */
      fprintf(stderr,"<4>bender_process_message returned an error: %d\n",errno);
      errno = 0;
      //pthread_exit(1); /* send the return message anyway */
   }

   useless = sizeof(struct sockaddr_in);
   res = sendto(info->socket,info->msg,bender_commsize(info->msg),0,info->target,useless);

   if (res == -1) {
      /* some call or action in the message processing has returned an error */
      fprintf(stderr,"<4>sendto returned an error: %d\n",errno);
      errno = 0;
   }

   pthread_exit(0);
}


size_t bender_commsize(struct bender_communication * msg) {
   return sizeof(msg->msg_type) + sizeof(msg->system_name) + 
          sizeof(msg->mac) + sizeof(msg->nonce) +
          sizeof(msg->message);
}

/* Basically strcmp, but allows the use of the character '%' to
 * short-circuit the comparison and store the remaining input in
 * args. This is done to allow some more flexability in the 
 * writing of messages that keeps me from writing the same
 * message with subtle variations over and over again.
 */
int bender_strmatch(char * target, char * input, char ** args) {

   static char * empty_string = "";

   if (args)
      *args = NULL;

   /* done because we are prestepping */
   --input; --target;

   while (*(++input) == *(++target) && *input && *target && *target != '%');

   if (*target == '%') {
      if (args)
         *args = input;
      return 1;
   }
   else if (args)
      *args = empty_string;

   if (*target == '\0' && *input == *target)
      return 1;

   return 0;
}

int bender_process_message(struct bender_communication * message, int * message_len,
                           struct bender_exec_metadata * meta, struct bender_exec_list * exec) {

   /* setup the return message */
   strncpy((char *)message->system_name,meta->bender_name,BENDER_SYSTEM_NAME_LEN-1);
   message->system_name[BENDER_SYSTEM_NAME_LEN-1] = '\0';
   message->msg_type = BENDERC_RESPONSE;

   char * args;

   struct bender_exec_list * curr = exec;
   while (curr != NULL) {

      if (bender_strmatch(curr->external_cmd,message->message,&args))
         break;

      curr = curr->next;
   }

   if (curr == NULL) {
      errno = EOPNOTSUPP;
      goto failure;
   }

   char cmd[1024];
   snprintf(cmd,1023,"exec bash -c '%s %s' 2>&1",curr->internal_cmd,args);

   {
      FILE * proc = popen(cmd,"r");

      int res = fread(message->message,sizeof(char),BENDER_MESSAGE_LEN,proc);
      if (res == 0) {
         errno = ESTRPIPE;
         goto failure;
      }
      *message_len = res+sizeof('\0');
      message->message[res] = '\0';

      pclose(proc);
   }

   return 0;

failure:
   {
      
      char fail_msg[24];
      snprintf(fail_msg,23,"\033[31mfailure: %d\033[0m",errno);

      return -1;

   }
}

enum bender_cmdfmt_state { BENDER_CMDFMT_UNSPEC=0, 
                           BENDER_CMDFMT_TYPE=1,
                           BENDER_CMDFMT_KEY=2,
                           BENDER_CMDFMT_VAL=3
                          };
int bender_generate_exec_list(char * path, struct bender_exec_list ** exec,
                              struct bender_exec_metadata * meta, int debug) {

   int retval = 0;

   char typename[32];
   struct bender_exec_list * new_exec = NULL;

   /* start by parsing the contents of the file into a buffer */

   char * buf;
   int buf_len = load(path,&buf);
   if (buf_len == -1)
      goto failure;

   int coll = 0;
   int loc_coll, loc_size, state, res;
   int linenum = 1, colnum = 1;

   /* now we can start parsing the arguments */

   enum bender_communication_type type;
   new_exec = calloc(1,sizeof(struct bender_exec_list));

   state = BENDER_CMDFMT_UNSPEC;
   while (coll < buf_len) {

      char c = buf[coll];

      switch (state) {
         case BENDER_CMDFMT_UNSPEC:
            {

               switch (c) {

                  default:
                     if ((retval = -1) && debug)
                        fprintf(stdout,"Error reading configuration file (%d:%d): "
                                       "extra characters before start of line\n", linenum,colnum);

                  case ';':
                  case '#':
                     while (buf[coll] != '\n') 
                        ++coll; 

                  case '\n':
                     ++linenum;
                     colnum = -1;
                     break;

                  case '[':
                     state = BENDER_CMDFMT_TYPE;
                     loc_coll = 0;
                     break;

               }

            }
            break;
         case BENDER_CMDFMT_TYPE:
            {

               switch (c) {

                  case ';':
                  case '#':
                     if ((retval = -1) && debug)
                        fprintf(stdout,"Error reading configuration file (%d:%d): "
                                       "comment before end of line\n", linenum,colnum);
                     while (buf[coll] != '\n') 
                        { ++coll; ++colnum; }

                  case '\n':
                     if ((retval = -1) && debug)
                        fprintf(stdout,"Error reading configuration file (%d:%d): "
                                       "premature end of line\n", linenum,colnum);
                     ++linenum;
                     colnum = -1;
                     state = BENDER_CMDFMT_UNSPEC;
                     break;

                  case ']':
                     typename[loc_coll] = '\0';
                     strtrm(typename);

                     if (!strcmp("ros",typename)) 
                        type = BENDERC_ROS;
                     else if (!strcmp("script",typename))
                        type = BENDERC_SCRIPT;
                     else if (!strcmp("echo",typename))
                        type = BENDERC_ECHO;
                     else if (!strcmp("exec",typename))
                        type = BENDERC_EXEC;
                     else if (!strcmp("internal",typename))
                        type = BENDERC_INTERNAL;
                     else if (!strcmp("response",typename))
                        type = BENDERC_RESPONSE;
                     else {
                        fprintf(stdout,"Error reading configuration file (%d:%d): "
                                       "unknown typename: |%s|\n",linenum,colnum,typename);
                        retval = -1;
                        type = BENDERC_ECHO;
                     }

                     new_exec->cmd_type = type;

                     loc_coll = 0;
                     loc_size = 24;
                     new_exec->external_cmd = malloc(sizeof(char)*loc_size);
                     if (new_exec->external_cmd == NULL)
                        goto failure;

                     state = BENDER_CMDFMT_KEY;
                     break;

                  default:
                     typename[loc_coll++] = c;

                     if (loc_coll > 23) {
                        if ((retval = -1) && debug)
                           fprintf(stdout,"Error reading configuration file (%d:%d): "
                                          "typename exceeds size limit\n", linenum,colnum);
                        while (buf[coll] != '\n') 
                           ++coll; 
                        ++linenum;
                        colnum = -1;
                        state = BENDER_CMDFMT_UNSPEC;
                     }

                     break;
                  }

            }
            break;
         case BENDER_CMDFMT_KEY:
            {

               switch (c) {

                  case ';':
                  case '#':
                     if ((retval = -1) && debug)
                        fprintf(stdout,"Error reading configuration file (%d:%d): "
                                       "comment before end of line\n", linenum,colnum);
                     while (buf[coll] != '\n') 
                        { ++coll; ++colnum; }

                  case '\n':
                     if ((retval = -1) && debug)
                        fprintf(stdout,"Error reading configuration file (%d:%d): "
                                       "premature end of line\n", linenum,colnum);
                     ++linenum;
                     colnum = -1;
                     state = BENDER_CMDFMT_UNSPEC;
                     break;

                  case '=':
                     new_exec->external_cmd[loc_coll] = '\0';

                     res = strtrm(new_exec->external_cmd);
                     if (res == -1)
                        goto failure;

                     new_exec->external_cmd = realloc(new_exec->external_cmd,res);

                     loc_coll = 0;
                     loc_size = 24;
                     new_exec->internal_cmd = malloc(sizeof(char)*loc_size);
                     if (new_exec->internal_cmd == NULL)
                        goto failure;

                     state = BENDER_CMDFMT_VAL;
                     break;

                  default:
                     new_exec->external_cmd[loc_coll++] = c;

                     if (loc_coll == loc_size) {
                        loc_size *= 2;
                        new_exec->external_cmd = realloc(new_exec->external_cmd,loc_size);
                        if (new_exec->external_cmd == NULL)
                           goto failure;
                     }

                     break;

               }

            }
            break;
         case BENDER_CMDFMT_VAL:
            {

               switch (c) {

                  case ';':
                  case '#':

                     /* we allow comments at the end of the line */
                     while (buf[coll] != '\n') 
                        ++coll;

                  case '\n':
                     new_exec->internal_cmd[loc_coll] = '\0';

                     res = strtrm(new_exec->internal_cmd);
                     if (res == -1)
                        goto failure;

                     new_exec->internal_cmd = strsep(&new_exec->internal_cmd,"%");

                     new_exec->internal_cmd = realloc(new_exec->internal_cmd,strlen(new_exec->internal_cmd) + sizeof('\0'));

                     goto finalize;
reset:

                     ++linenum;
                     colnum = -1;
                     state = BENDER_CMDFMT_UNSPEC;
                     break;

                  default:
                     new_exec->internal_cmd[loc_coll++] = c;

                     if (loc_coll == loc_size) {
                        loc_size *= 2;
                        new_exec->internal_cmd = realloc(new_exec->internal_cmd,loc_size);
                        if (new_exec->internal_cmd == NULL)
                           goto failure;
                     }

                     break;

               }

            }
            break;
         default:
            /* xD */
            break;
      }

      ++colnum;
      ++coll;

   }


finish:

   if (new_exec) {
      free(new_exec->external_cmd);
      free(new_exec->internal_cmd);
   }
   free(new_exec);
   free(buf);

   return retval;

failure:
   {
      retval = -1;
      bender_degenerate_exec_list(exec);
      goto finish;
   }

finalize:
   {

      char * newbuf = malloc(sizeof(char)*(res+128));

      switch (type) {
         case BENDERC_RESTART:

            strcpy(newbuf,"echo 'restarting...'");
            free(new_exec->internal_cmd);
            new_exec->internal_cmd = realloc(newbuf,strlen(newbuf) + sizeof('\0'));
            if (new_exec->internal_cmd == NULL)
               goto failure;

            break;
         case BENDERC_ROS:

            res = snprintf(newbuf,res+128,". /opt/ros/%s/setup.sh; "
                                          ". %s/scripts/setup.sh; "
                                          "/opt/ros/%s/bin/ros2 %s",
                           meta->ros_version, meta->bender_path, meta->ros_version,
                           new_exec->internal_cmd) + sizeof('\0');
            free(new_exec->internal_cmd);
            new_exec->internal_cmd = realloc(newbuf,res);

            if (new_exec->internal_cmd == NULL)
               goto failure;

            break;
         case BENDERC_SCRIPT:

            res = snprintf(newbuf,res+128,". /opt/ros/%s/setup.sh; "
                                          ". %s/scripts/setup.sh; "
                                          "%s/scripts/%s",
                           meta->ros_version, meta->bender_path, meta->bender_path, 
                           new_exec->internal_cmd) + sizeof('\0');
            free(new_exec->internal_cmd);
            new_exec->internal_cmd = realloc(newbuf,res);

            if (new_exec->internal_cmd == NULL)
               goto failure;

            break;
         case BENDERC_EXEC:
            
            res = snprintf(newbuf,res+128,". /opt/ros/%s/setup.sh; "
                                          ". %s/scripts/setup.sh; "
                                          "%s",
                           meta->ros_version, meta->bender_path, 
                           new_exec->internal_cmd) + sizeof('\0');
            free(new_exec->internal_cmd);
            new_exec->internal_cmd = realloc(newbuf,res);

            if (new_exec->internal_cmd == NULL)
               goto failure;

            break;
         case BENDERC_ECHO:
         case BENDERC_INTERNAL:
         case BENDERC_RESPONSE:

            res = snprintf(newbuf,res+128,". /opt/ros/%s/setup.sh; "
                                          ". %s/scripts/setup.sh; "
                                          "echo \"%s\"",
                           meta->ros_version, meta->bender_path, 
                           new_exec->internal_cmd) + sizeof('\0');
            free(new_exec->internal_cmd);
            new_exec->internal_cmd = realloc(newbuf,res);

            if (new_exec->internal_cmd == NULL)
               goto failure;

            break;
      }

      new_exec->next = *exec;
      *exec = new_exec;

      /* load a new shell in */
      new_exec = calloc(1,sizeof(struct bender_exec_list));

      goto reset;
   }
}

int bender_degenerate_exec_list(struct bender_exec_list ** exec) {

   if (!exec)
      return 0;

   struct bender_exec_list * next;
   while (*exec != NULL) {
      next = (*exec)->next;
      free((*exec)->external_cmd);
      free((*exec)->internal_cmd);
      free(*exec);
      *exec = next;
   }

   return 0;
}

void bender_encrypt_message(struct bender_communication * msg, struct gost_opt * opts) {

   if (msg->msg_type & BENDER_ENCRYPTED)
      return;

   msg->nonce = opts->initialization_const;

   char * msg_start = msg->system_name;
   size_t msg_len = (sizeof(msg->system_name) + sizeof(msg->message)) / 8;

   gost_mac(&msg->mac,(uint64_t *)msg_start,msg_len,opts);

   gost_encrypt((uint64_t *)msg_start,msg_len,opts);

   msg->msg_type |= BENDER_ENCRYPTED;
}

int bender_decrypt_message(struct bender_communication * msg, struct gost_opt * opts) {

   if (!(msg->msg_type & BENDER_ENCRYPTED))
      return 0;

   msg->nonce = opts->initialization_const;

   char * msg_start = msg->system_name;
   size_t msg_len = (sizeof(msg->system_name) + sizeof(msg->message)) / 8;

   gost_decrypt((uint64_t *)msg_start,msg_len,opts);

   uint32_t mac;
   gost_mac(&mac,(uint64_t *)msg_start,msg_len,opts);

   if (msg->mac != mac)
      return 0;

   msg->msg_type &= ~BENDER_ENCRYPTED;

   return 1;
}
