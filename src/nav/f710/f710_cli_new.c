
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>
#include <signal.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

int interrupted;

#define PORT 8333
#define BUF_LEN 1024
#define POLL_RATE 0.125
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

/* invert motor 0's direction if invert m0
 * is set */
#ifdef INVERTM0
#define M0_MULT -1
#else
#define M0_MULT 1
#endif

/* invert motor 1's direction if invert m1
 * is set */
#ifdef INVERTM1
#define M1_MULT -1
#else
#define M1_MULT 1
#endif

/* invert drum's direction if invert dr
 * is set */
#ifdef INVERTDR
#define DR_MULT -1
#else
#define DR_MULT 1
#endif

/* invert arm's direction if invert ar
 * is set */
#ifdef INVERTAR
#define AR_MULT -1
#else
#define AR_MULT 1
#endif

struct f710_status {
   int8_t on;
   int8_t vibrate;
   int8_t mode;
   int8_t start;
   int8_t back;
   int8_t dir;
   int8_t y;
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
#define NANOSECONDS_PER_SECOND 1e9
/* return the montotomic clock time in nanoseconds */
clock_t CLOCK();

void interrupt_func(int code) {
   interrupted = 1;
}

int main(int argc, char ** argv) {

   interrupted = 0;

   signal(SIGINT,interrupt_func);

   if (argc != 3) {
      printf("\033[31musage:\033[0m\n%s [controller] [ip-addr]\n",argv[0]);
      exit(1);
   }

   struct sockaddr_in connaddr;
   int connfd;

   connfd = socket(AF_INET,SOCK_STREAM,0);

   if (connfd == -1) {
      printf("failed to open connection port\n");
      perror("socket");
   }


   bzero(&connaddr,sizeof(connaddr));
   inet_pton(AF_INET,argv[2],&connaddr.sin_addr);
   connaddr.sin_family = AF_INET;
   connaddr.sin_port = htons(PORT);

   if (-1 == connect(connfd,(struct sockaddr *)&connaddr,sizeof(connaddr))) {
      printf("failed to connect to remote server\n");
      perror("connect");
   }

   int controller;

   if ( (controller = open(argv[1],O_RDONLY)) == -1) {
      printf("failed to open controller at %s\n",argv[1]);
      perror("open");
      exit(1);
   }

   long recved = 0x7f7f7f7f00;
   write(connfd,&recved,sizeof(long));
   write(connfd,&recved,sizeof(long));
   write(connfd,&recved,sizeof(long));
   write(connfd,&recved,sizeof(long));
   write(connfd,&recved,sizeof(long));
   write(connfd,&recved,sizeof(long));

   double track_speed_scaler = 1.0;
   uint16_t drum_speed_scaler = 100;
   uint16_t arm_speed_scaler = 10;
   int16_t arm_pos;
   int16_t drum_speed;

   fd_set read_set;

   struct f710_status stat;

   clock_t last_clock = CLOCK();
   double time_dist = 0.0;
   double left_speed, right_speed;

   struct timeval wait_max;

   int tick_time = 0;

   while (!interrupted) {

      tick_time = 0;

      FD_ZERO(&read_set);
      FD_SET(controller,&read_set);
      bzero(&wait_max,sizeof(wait_max));
      wait_max.tv_sec = 0;
      wait_max.tv_usec = (int)(POLL_RATE * 1e6);

      int res = select(controller+1,&read_set,NULL,NULL,&wait_max);

      if (res > 0) {

         read(controller,&recved,sizeof(long));

         write(connfd,&recved,sizeof(long));

         update_status(recved,&stat);
      }

      printf("\033[2J\033[H");
      printf("\033[31m!!! ESTIMATED VALUES ONLY !!!\033[0m\n\n");
      printf("vibrate:          %s\n",stat.vibrate ? "ON" : "OFF");
      printf("odrive max speed: %f\n",track_speed_scaler);
      printf("drum speed:       %d\n",drum_speed_scaler);
      printf("arm speed:        %d\n",arm_speed_scaler);
      printf("arm pos:          %d\n",arm_pos);
      printf("drum speed:       %d\n",drum_speed);
      printf("odrive0 speed:    %f\n",left_speed * M0_MULT);
      printf("odrive1 speed:    %f\n",right_speed * M1_MULT);

      time_dist = (double)(CLOCK() - last_clock) / NANOSECONDS_PER_SECOND;
      if (time_dist > POLL_RATE) {
         last_clock = CLOCK();
         tick_time = 1;
      }

      if (stat.mode) {
         // TODO: add the mode brayden wanted 
      }
      else {

         left_speed = track_speed_scaler * M0_MULT * (((double)(stat.lv_fr - 127) * -1) / 128.0);
         right_speed = track_speed_scaler * M1_MULT * (((double)(stat.rv_fr - 127) * -1) / 128.0);

         left_speed  = (fabs(left_speed)  < 0.1 * track_speed_scaler) ? 0.0 : left_speed;
         right_speed = (fabs(right_speed) < 0.1 * track_speed_scaler) ? 0.0 : right_speed;

         if (stat.a) {
            left_speed = 0;
            drum_speed = 0;
         }
         else if (stat.b) {
            drum_speed = 0;
         }

         if (tick_time) {

            if (stat.lb) {
               drum_speed = drum_speed_scaler * DR_MULT;
            }
            else if (stat.lt) {
               drum_speed = -drum_speed_scaler * DR_MULT;
            }

            if (stat.rb) {
               arm_pos += arm_speed_scaler * AR_MULT;
            }
            else if (stat.rt) {
               arm_pos -= arm_speed_scaler * AR_MULT;
            }

            if (stat.vibrate) {

               switch (stat.dir) {

                  case DIR_NORTH:

                     track_speed_scaler += 1.0;
                     track_speed_scaler 
                        = (track_speed_scaler > MAX_TRACK_SPEED ? MAX_TRACK_SPEED : track_speed_scaler);

                     break;
                  case DIR_SOUTH:

                     track_speed_scaler -= 1.0;
                     track_speed_scaler 
                        = (track_speed_scaler < 0.0 ? 0.0 : track_speed_scaler);

                     break;
                  case DIR_EAST:

                     drum_speed_scaler += 10;
                     drum_speed_scaler
                        = (drum_speed_scaler > MAX_DRUM_SPEED ? MAX_DRUM_SPEED : drum_speed_scaler);

                     break;
                  case DIR_WEST:

                     drum_speed_scaler -= 10;
                     drum_speed_scaler
                        = (drum_speed_scaler < 0 ? 0 : drum_speed_scaler);

                     break;

               }

               if (stat.start) {

                  arm_speed_scaler += 10;
                  arm_speed_scaler
                     = (arm_speed_scaler > MAX_ARM_SPEED ? MAX_ARM_SPEED : arm_speed_scaler);

               }
               else if (stat.back) {

                  arm_speed_scaler -= 10;
                  arm_speed_scaler
                     = (arm_speed_scaler < 0 ? 0 : arm_speed_scaler);

               }

            }

         }

      }

   }

   close(controller);
   close(connfd);

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

clock_t CLOCK() {
   struct timespec uptime;
   clock_gettime(CLOCK_MONOTONIC,&uptime);
   return 1e9 * uptime.tv_sec + uptime.tv_nsec;
}
