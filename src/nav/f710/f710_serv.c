<<<<<<< HEAD

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
/* print some information about the status of the
 * controller input.                             */
void print_status(struct f710_status * stat);
/* sets the speed of the given odrive */
void set_odrive_speed(int odrive, double speed);
/* gets the speed of the given odrive */
double get_odrive_speed(int odrive);
/* sets the speed of the drum */
void set_drum_speed(int teensy, int16_t speed);
/* set the position of the arm */
void set_arm_pos(int teensy, int16_t pos);
/* get the position of the arm */
int16_t get_arm_pos(int teensy);
#define NANOSECONDS_PER_SECOND 1e9
/* return the montotomic clock time in nanoseconds */
clock_t CLOCK();

int interrupted = 0;

void interrupt_func(int code) {
   interrupted = 1;
}

/* the function we are running through */
void * thread_loop(void * arg);
/* to test stuff brrrrrrr */
void * minimal_loop(void * arg);

struct path_strings {
   char * odrive0;
   char * odrive1;
   char * teensy;
   int f710;
   int * arm_pos;
};

int main(int argc, char ** argv) {

   if (argc != 4) {
      printf("\033[31musage:\033[0m\n%s [odrive0] [odrive1] [teensy]\n",argv[0]);
      exit(1);
   }

   int arm_pos = 0;

   struct path_strings paths;
   bzero(&paths,sizeof(paths));
   paths.odrive0 = argv[1];
   paths.odrive1 = argv[2];
   paths.teensy = argv[3];
   paths.arm_pos = &arm_pos;

   struct path_strings * sent_paths[128];
   int sent_num = 0;

   int listenfd;
   int connfd;

   listenfd = socket(AF_INET,SOCK_STREAM,0);

   if (listenfd == -1) {
      printf("failed to open listening socket\n");
      perror("socket");
      exit(1);
   }

   struct sockaddr_in listen_addr;
   bzero(&listen_addr,sizeof(listen_addr));
   listen_addr.sin_family = AF_INET;
   listen_addr.sin_port = htons(PORT);
   listen_addr.sin_addr.s_addr = htonl(INADDR_ANY);

   if (-1 == bind(listenfd, (struct sockaddr *)&listen_addr, sizeof(listen_addr))) {
      printf("failed to bind to address\n");
      perror("bind");
      exit(1);
   }

   if (-1 == listen(listenfd,5)) {
      printf("failed to start listening\n");
      perror("listen");
      exit(1);
   }

   for ( ; ; ) {

      struct sockaddr_in new_addr;
      socklen_t new_addr_len;

      connfd = accept(listenfd,(struct sockaddr *)&new_addr,&new_addr_len);

      sent_paths[sent_num] = malloc(sizeof(struct path_strings));

      memcpy(sent_paths[sent_num],&paths,sizeof(struct path_strings));
      sent_paths[sent_num]->f710 = connfd;


      pthread_t th;

      pthread_create(&th,NULL,thread_loop,(void *)sent_paths[sent_num]);

      sent_num += 1;

   }

   return 0;
}

void * minimal_loop(void * arg) {

   pthread_detach(pthread_self());

   struct path_strings * paths = (struct path_strings *)arg;

   signal(SIGINT,interrupt_func);

   int controller = paths->f710;

   if (controller == -1) {
      printf("passed bad controller address\n");
      pthread_exit(0);
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

void * thread_loop(void * arg) {

   pthread_detach(pthread_self());

   struct path_strings * paths = (struct path_strings *)arg;

   signal(SIGINT,interrupt_func);

   int controller;
   int teensy;
   int odrive0;
   int odrive1;

   if ( (odrive0 = open(paths->odrive0,O_RDWR)) == -1) {
      printf("\033[31mfailed to connect to odrive0 at %s\033[0m\n",paths->odrive0);
      perror("open");
      exit(1);
   }
   printf("\033[36mconnected to odrive0\033[0m\n");

   if ( (odrive1 = open(paths->odrive1,O_RDWR)) == -1) {
      printf("\033[31mfailed to connect to odrive1 at %s\033[0m\n",paths->odrive1);
      perror("open");
      exit(1);
   }
   printf("\033[36mconnected to odrive1\033[0m\n");

   if ( (teensy = open(paths->teensy,O_RDWR)) == -1) {
      printf("\033[31mfailed to connect to teensy at %s\033[0m\n",paths->teensy);
      perror("open");
      exit(1);
   }
   printf("\033[36mconnected to teensy\033[0m\n");

   if ( (controller = paths->f710) == -1) {
      printf("\033[31mgot bad controller address\033[0m\n");
   }
   printf("\033[36mconnected to controller\033[0m\n");

   set_odrive_speed(odrive0,0);
   set_odrive_speed(odrive1,0);
   set_arm_pos(teensy,0);

   double track_speed_scaler = 1.0;
   uint16_t drum_speed_scaler = 100;
   uint16_t arm_speed_scaler = 10;

   fd_set read_set;

   long raw_stat;
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
      //select(controller+1,&read_set,NULL,NULL,NULL);

      if (res > 0) {
         if (!read(controller,&raw_stat,8))
            pthread_exit(0);

         update_status(raw_stat,&stat);
      }

      print_status(&stat);

      printf("odrive max speed: %f\n",track_speed_scaler);
      printf("drum speed:       %d\n",drum_speed_scaler);
      printf("arm speed:        %d\n",arm_speed_scaler);
      printf("arm pos:          %d\n",*paths->arm_pos);
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

         set_odrive_speed(odrive0,left_speed);
         set_odrive_speed(odrive1,right_speed);

         if (stat.a) {
            set_odrive_speed(odrive0,0);
            set_odrive_speed(odrive1,0);
            set_drum_speed(teensy,0);
         }
         else if (stat.b) {
            set_drum_speed(teensy,0);
         }

         if (tick_time) {

            if (stat.lb) {
               set_drum_speed(teensy,drum_speed_scaler * DR_MULT);
            }
            else if (stat.lt) {
               set_drum_speed(teensy,-drum_speed_scaler * DR_MULT);
            }

            if (stat.rb) {
               *paths->arm_pos += arm_speed_scaler * AR_MULT;
               set_arm_pos(teensy,*paths->arm_pos);
            }
            else if (stat.rt) {
               *paths->arm_pos -= arm_speed_scaler * AR_MULT;
               set_arm_pos(teensy,*paths->arm_pos);
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
   close(teensy);
   close(odrive0);
   close(odrive1);

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

}

void set_odrive_speed(int odrive, double speed) {

   char buf[BUF_LEN];

   snprintf(buf,BUF_LEN,"v 0 %f\n", speed );

   write(odrive,buf,strlen(buf));
}

void get_response(int src, int num, double * res) {

   char buf[BUF_LEN];
   char * pos = buf;
   char * nextpos = NULL;

   int count = read(src,buf,sizeof(buf)-1);
   buf[count] = '\0';

   for (int i = 0; i < num && pos; ++i) {
      res[i] = strtod(pos,&nextpos);
      pos = nextpos;
   }
}

double get_odrive_speed(int odrive) {

   char buf[BUF_LEN];

   double motors[2];
   snprintf(buf,BUF_LEN,"f 0\n");
   write(odrive,buf,strlen(buf));
   get_response(odrive,2,motors);

   return motors[1];
}

void set_drum_speed(int teensy, int16_t speed) {

   char buf[BUF_LEN];

   snprintf(buf,BUF_LEN,"SET_DRUM %d\n",speed);
   write(teensy,buf,strlen(buf));
}

void set_arm_pos(int teensy, int16_t pos) {

   char buf[BUF_LEN];

   snprintf(buf,BUF_LEN,"SET_ARM %d\n",pos);
   write(teensy,buf,strlen(buf));
}

int16_t get_arm_pos(int teensy) {

   double pos;

   char buf[BUF_LEN];
   snprintf(buf,BUF_LEN,"GET_ARM\n");
   write(teensy,buf,strlen(buf));
   get_response(teensy,1,&pos);

   return (int16_t)pos;
}

clock_t CLOCK() {
   struct timespec uptime;
   clock_gettime(CLOCK_MONOTONIC,&uptime);
   return 1e9 * uptime.tv_sec + uptime.tv_nsec;
}

||||||| parent of 8483cb5 (fixes to make the judges happy)
=======

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
/* print some information about the status of the
 * controller input.                             */
void print_status(struct f710_status * stat);
/* sets the speed of the given odrive */
void set_odrive_speed(int odrive, double speed);
/* gets the speed of the given odrive */
double get_odrive_speed(int odrive);
/* sets the speed of the drum */
void set_drum_speed(int teensy, int16_t speed);
/* set the position of the arm */
void set_arm_pos(int teensy, int16_t pos);
/* get the position of the arm */
uint16_t get_arm_pos(int teensy);
#define NANOSECONDS_PER_SECOND 1e9
/* return the montotomic clock time in nanoseconds */
clock_t CLOCK();

int interrupted = 0;

void interrupt_func(int code) {
   interrupted = 1;
}

/* the function we are running through */
void * thread_loop(void * arg);
/* to test stuff brrrrrrr */
void * minimal_loop(void * arg);

struct path_strings {
   char * odrive0;
   char * odrive1;
   char * teensy;
   int f710;
};

int main(int argc, char ** argv) {

   if (argc != 4) {
      printf("\033[31musage:\033[0m\n%s [odrive0] [odrive1] [teensy]\n",argv[0]);
      exit(1);
   }

   struct path_strings paths;
   bzero(&paths,sizeof(paths));
   paths.odrive0 = argv[1];
   paths.odrive1 = argv[2];
   paths.teensy = argv[3];

   struct path_strings * sent_paths[128];
   int sent_num = 0;

   int listenfd;
   int connfd;

   listenfd = socket(AF_INET,SOCK_STREAM,0);

   if (listenfd == -1) {
      printf("failed to open listening socket\n");
      perror("socket");
      exit(1);
   }

   struct sockaddr_in listen_addr;
   bzero(&listen_addr,sizeof(listen_addr));
   listen_addr.sin_family = AF_INET;
   listen_addr.sin_port = htons(PORT);
   listen_addr.sin_addr.s_addr = htonl(INADDR_ANY);

   if (-1 == bind(listenfd, (struct sockaddr *)&listen_addr, sizeof(listen_addr))) {
      printf("failed to bind to address\n");
      perror("bind");
      exit(1);
   }

   if (-1 == listen(listenfd,5)) {
      printf("failed to start listening\n");
      perror("listen");
      exit(1);
   }

   for ( ; ; ) {

      struct sockaddr_in new_addr;
      socklen_t new_addr_len;

      connfd = accept(listenfd,(struct sockaddr *)&new_addr,&new_addr_len);

      sent_paths[sent_num] = malloc(sizeof(struct path_strings));

      memcpy(&sent_paths[sent_num],&paths,sizeof(struct path_strings));
      sent_paths[sent_num]->f710 = connfd;

      pthread_t th;

      pthread_create(&th,NULL,minimal_loop,(void *)sent_paths[sent_num]);

   }

   return 0;
}

void * minimal_loop(void * arg) {

   pthread_detach(pthread_self());

   struct path_strings * paths = (struct path_strings *)arg;

   signal(SIGINT,interrupt_func);

   int controller = paths->f710;

   if (controller == -1) {
      printf("passed bad controller address\n");
      pthread_exit(0);
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

void * thread_loop(void * arg) {

   pthread_detach(pthread_self());

   struct path_strings * paths = (struct path_strings *)arg;

   signal(SIGINT,interrupt_func);

   int controller;
   int teensy;
   int odrive0;
   int odrive1;

   if ( (odrive0 = open(paths->odrive0,O_RDWR)) == -1) {
      printf("\033[31mfailed to connect to odrive0 at %s\033[0m\n",paths->odrive0);
      perror("open");
      exit(1);
   }
   printf("\033[36mconnected to odrive0\033[0m\n");

   if ( (odrive1 = open(paths->odrive1,O_RDWR)) == -1) {
      printf("\033[31mfailed to connect to odrive1 at %s\033[0m\n",paths->odrive1);
      perror("open");
      exit(1);
   }
   printf("\033[36mconnected to odrive1\033[0m\n");

   if ( (teensy = open(paths->teensy,O_RDWR)) == -1) {
      printf("\033[31mfailed to connect to teensy at %s\033[0m\n",paths->teensy);
      perror("open");
      exit(1);
   }
   printf("\033[36mconnected to teensy\033[0m\n");

   if ( (controller = paths->f710) == -1) {
      printf("\033[31mgot bad controller address\033[0m\n");
   }
   printf("\033[36mconnected to controller\033[0m\n");

   set_odrive_speed(odrive0,0);
   set_odrive_speed(odrive1,0);

   double track_speed_scaler = 1.0;
   uint16_t drum_speed_scaler = 100;
   uint16_t arm_speed_scaler = 10;

   fd_set read_set;

   long raw_stat = 0x7f7f7f7f00;
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
      //select(controller+1,&read_set,NULL,NULL,NULL);

      if (res > 0)
         if (!read(controller,&raw_stat,8))
            pthread_exit(0);

      update_status(raw_stat,&stat);

      print_status(&stat);

      printf("odrive max speed: %f\n",track_speed_scaler);
      printf("drum speed:       %d\n",drum_speed_scaler);
      printf("arm speed:        %d\n",arm_speed_scaler);
      printf("arm pos:          %d\n",get_arm_pos(teensy));
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

         set_odrive_speed(odrive0,left_speed);
         set_odrive_speed(odrive1,right_speed);

         if (stat.a) {
            set_odrive_speed(odrive0,0);
            set_odrive_speed(odrive1,0);
            set_drum_speed(teensy,0);
         }
         else if (stat.b) {
            set_drum_speed(teensy,0);
         }

         if (tick_time) {

            if (stat.lb) {
               set_drum_speed(teensy,drum_speed_scaler * DR_MULT);
            }
            else if (stat.lt) {
               set_drum_speed(teensy,-drum_speed_scaler * DR_MULT);
            }

            if (stat.rb) {
               uint16_t pos = get_arm_pos(teensy);
               set_arm_pos(teensy,pos + arm_speed_scaler * AR_MULT);
            }
            else if (stat.rt) {
               uint16_t pos = get_arm_pos(teensy);
               set_arm_pos(teensy,pos - arm_speed_scaler * AR_MULT);
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
   close(teensy);
   close(odrive0);
   close(odrive1);

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

void set_odrive_speed(int odrive, double speed) {

   char buf[BUF_LEN];

   snprintf(buf,BUF_LEN,"v 0 %f\n", speed );

   write(odrive,buf,strlen(buf));
}

void get_response(int src, int num, double * res) {

   char buf[BUF_LEN];
   char * pos = buf;
   char * nextpos = NULL;

   int count = read(src,buf,sizeof(buf)-1);
   buf[count] = '\0';

   for (int i = 0; i < num && pos; ++i) {
      res[i] = strtod(pos,&nextpos);
      pos = nextpos;
   }
}

double get_odrive_speed(int odrive) {

   char buf[BUF_LEN];

   double motors[2];
   snprintf(buf,BUF_LEN,"f 0\n");
   write(odrive,buf,strlen(buf));
   get_response(odrive,2,motors);

   return motors[1];
}

void set_drum_speed(int teensy, int16_t speed) {

   char buf[BUF_LEN];

   snprintf(buf,BUF_LEN,"SET_DRUM %d\n",speed);
   write(teensy,buf,strlen(buf));
}

void set_arm_pos(int teensy, int16_t pos) {

   char buf[BUF_LEN];

   snprintf(buf,BUF_LEN,"SET_ARM %d\n",pos);
   write(teensy,buf,strlen(buf));
}

uint16_t get_arm_pos(int teensy) {

   double pos;

   char buf[BUF_LEN];
   snprintf(buf,BUF_LEN,"GET_ARM\n");
   write(teensy,buf,strlen(buf));
   get_response(teensy,1,&pos);

   return (uint16_t)pos;
}

clock_t CLOCK() {
   struct timespec uptime;
   clock_gettime(CLOCK_MONOTONIC,&uptime);
   return 1e9 * uptime.tv_sec + uptime.tv_nsec;
}

>>>>>>> 8483cb5 (fixes to make the judges happy)
