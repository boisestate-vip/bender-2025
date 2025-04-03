

#ifndef __BENEDER_COMMUNICATION

#define __BENEDER_COMMUNICATION
#include "gost.h"

/* communication helper functions and struct definitions for
 * messaging between the command and the server             */

#include <stdint.h>
#include <stdlib.h>

enum bender_communication_type { BENDERC_RESTART=0, 
                                 BENDERC_ROS=1, 
                                 BENDERC_SCRIPT=2,
                                 BENDERC_ECHO=3,
                                 BENDERC_EXEC=4,
                                 BENDERC_INTERNAL=5,
                                 BENDERC_RESPONSE=6
                                };

#define BENDER_SYSTEM_NAME_LEN 16
#define BENDER_MESSAGE_LEN     2048

#define BENDER_DEFAULT_PORT 47600

#define BENDER_ENCRYPTED 0x80


/* all the communication will be held through this struct */
struct bender_communication {
   char msg_type;
   uint32_t mac;
   uint64_t nonce;
   char system_name[BENDER_SYSTEM_NAME_LEN];
   char message[BENDER_MESSAGE_LEN];
};

struct bender_exec_metadata {
   char * ros_version;
   char * bender_name;
   char * bender_path;
};

struct bender_exec_list {
   enum bender_communication_type cmd_type;
   char * external_cmd;
   char * internal_cmd;
   struct bender_exec_list * next;
};

/* return the size of the bender_communication message */
size_t bender_commsize(struct bender_communication * msg);

/* perform encryption on a message and fill the nessesary fields */
void bender_encrypt_message(struct bender_communication * msg, struct gost_opt * opts);

/* perform decryption on a message and modify the nessesary fields 
 * return 1 if mac value from decryption matches mac provided     */
int bender_decrypt_message(struct bender_communication * msg, struct gost_opt * opts);

/* returns 1 if the given strings match (0 otherwise), or if they match 
 * up to and excluding the character '%' in the target. Return
 * also the string str after the '%' char in target as args if it is not null. */
int bender_strmatch(char * target, char * str, char ** args);

/* perform all the processing on the message and return an updated
 * message struct containing the response to return to the caller,
 * with the new message length being  returned in message_len */
int bender_process_message(struct bender_communication * message, int * message_len, 
                           struct bender_exec_metadata * meta, struct bender_exec_list * exec);

/* generate the execution list given a config file */
int bender_generate_exec_list(char * path, struct bender_exec_list ** exec,
                              struct bender_exec_metadata * meta, int debug);

/* free all data assoiciated with the execution list */
int bender_degenerate_exec_list(struct bender_exec_list ** exec);

#endif
