
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>
#include <signal.h>
#include <time.h>

#define BUF_LEN 1024
#define POLL_RATE 0.1
#define MAX_TRACK_SPEED 20.0
#define MAX_DRUM_SPEED 256
#define MAX_ARM_SPEED 200

#define DIR_CENTER 8
#define DIR_NORTH 0
#define DIR_SOUTH 4
#define DIR_WEST 6
#define DIR_EAST 2
#define DIR_SOUTHWEST 5
#define DIR_SOUTHEAST 3
#define DIR_NORTHEAST 1
#define DIR_NORTHWEST 7

#define CONTROL_ON 0x1000000000000000
#define VIBRATE_ON 0x2000000000000000
#define MODE_ON    0x0800000000000000
#define Y_DOWN     0x0000800000000000
#define X_DOWN     0x0000100000000000
#define A_DOWN     0x0000200000000000
#define B_DOWN     0x0000400000000000
#define LT_DOWN    0x0004000000000000
#define LB_DOWN    0x0001000000000000
#define RT_DOWN    0x0008000000000000
#define RB_DOWN    0x0002000000000000
#define START_DOWN 0x0020000000000000
#define BACK_DOWN  0x0010000000000000

#define PRESSED 1
#define RELEASED 0

struct f710_status {
   int8_t on;
   int8_t vibrate;
   int8_t mode;
   int8_t start;
   int8_t back;
   int8_t dir;
<<<<<<< HEAD
   int8_t y;
=======
 t  int8_t y;
>>>>>>> 40fd567 (working keyboard setup)
   int8_t x;
   int8_t a;
   int8_t b;
   int8_t lt;
   int8_t lb;
   int8_t rt;
   int8_t rb;
   uint8_t lv_fr;
   uint8_t lv_lr;
   uint8_t rv_fr;
   uint8_t rv_lr;
};

/* change the values in the given status struct based
 * on the value of the given long.                   */
void update_status(long og, struct f710_status * stat);
/* print some information about the status of the
 * controller input.                             */
void print_status(struct f710_status * stat);

int interrupted = 0;

void interrupt_func(int code) {
   interrupted = 1;
}

int main(int argc, char ** argv) {

   signal(SIGINT,interrupt_func);

   if (argc != 2) {
      printf("usage\n%s [f710]\n",argv[0]);
      exit(1);
   }

   int controller;

   if ( (controller = open(argv[1],O_RDONLY)) == -1) {
      printf("\033[31mfailed to connect to controller at %s\033[0m\n",argv[1]);
      perror("open");
      exit(1);
   }
   printf("\033[36mconnected to controller\033[0m\n");

   fd_set read_set;

   long raw_stat;
   struct f710_status stat;

   while (!interrupted) {

      FD_ZERO(&read_set);
      FD_SET(controller,&read_set);

      select(controller+1,&read_set,NULL,NULL,NULL);

      read(controller,&raw_stat,8);

      update_status(raw_stat,&stat);

      print_status(&stat);

   }

   close(controller);

   return 0;
}

#define UPDATE_FLAG(og,stat,flag,val) \
   if (og & val)                      \
      stat->flag = PRESSED;           \
   else                               \
      stat->flag = RELEASED

void update_status(long og, struct f710_status * stat) {

   UPDATE_FLAG(og,stat,vibrate,VIBRATE_ON);
   UPDATE_FLAG(og,stat,on,CONTROL_ON);
   UPDATE_FLAG(og,stat,mode,MODE_ON);
   UPDATE_FLAG(og,stat,start,START_DOWN);
   UPDATE_FLAG(og,stat,back,BACK_DOWN);
   UPDATE_FLAG(og,stat,y,Y_DOWN);
   UPDATE_FLAG(og,stat,x,X_DOWN);
   UPDATE_FLAG(og,stat,a,A_DOWN);
   UPDATE_FLAG(og,stat,b,B_DOWN);
   UPDATE_FLAG(og,stat,lt,LT_DOWN);
   UPDATE_FLAG(og,stat,lb,LB_DOWN);
   UPDATE_FLAG(og,stat,rt,RT_DOWN);
   UPDATE_FLAG(og,stat,rb,RB_DOWN);

   stat->dir   = (og >> 40) & 0xf;
   stat->lv_fr = (og >> 16) & 0xff;
   stat->lv_lr = (og >>  8) & 0xff;
   stat->rv_fr = (og >> 32) & 0xff;
   stat->rv_lr = (og >> 24) & 0xff;

}

void print_status(struct f710_status * stat) {

   printf("\033[2J\033[H");
   printf("vibrate: [%4s]\t on:    [%4s]\n",
         (stat->vibrate == 1) ? "DOWN" : "UP",
         (stat->on == 1) ? "DOWN" : "UP");
   printf("mode:    [%4s]\t start: [%4s]\n",
         (stat->mode == 1) ? "DOWN" : "UP",
         (stat->start == 1) ? "DOWN" : "UP");
   printf("back:    [%4s]\n",
         (stat->back == 1) ? "DOWN" : "UP");
   printf("x:       [%4s]\t y:     [%4s]\n",
         (stat->x == 1) ? "DOWN" : "UP",
         (stat->y == 1) ? "DOWN" : "UP");
   printf("a:       [%4s]\t b:     [%4s]\n",
         (stat->a == 1) ? "DOWN" : "UP",
         (stat->b == 1) ? "DOWN" : "UP");
   printf("lt:      [%4s]\t lb:    [%4s]\n",
         (stat->lt == 1) ? "DOWN" : "UP",
         (stat->lb == 1) ? "DOWN" : "UP");
   printf("rt:      [%4s]\t rb:    [%4s]\n",
         (stat->rt == 1) ? "DOWN" : "UP",
         (stat->rb == 1) ? "DOWN" : "UP");

   switch (stat->dir) {
      case DIR_CENTER:
         printf("dir: center\n");
         break;
      case DIR_NORTH:
         printf("dir: north\n");
         break;
      case DIR_SOUTH:
         printf("dir: south\n");
         break;
      case DIR_EAST:
         printf("dir: east\n");
         break;
      case DIR_WEST:
         printf("dir: west\n");
         break;
      case DIR_NORTHEAST:
         printf("dir: northeast\n");
         break;
      case DIR_NORTHWEST:
         printf("dir: northwest\n");
         break;
      case DIR_SOUTHWEST:
         printf("dir: southwest\n");
         break;
      case DIR_SOUTHEAST:
         printf("dir: southeast\n");
         break;
      default:
         printf("dir: unknown\n");
         break;
   }

   printf("lv: %u %u\n",stat->lv_fr,stat->lv_lr);
   printf("rv: %u %u\n",stat->rv_fr,stat->rv_lr);

}
