
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/select.h>

/* print bytes written and read if we 
 * are in debug mode */
#ifdef DEBUG
#define pw(x) printf("bytes moved: %d\n",x);
#else
#define pw(x) do { (void)x; } while (0)
#endif

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

void print_response(int src) {

   char buf[2048];

   int res = read(src,buf,sizeof(buf)-1);
   buf[res] = '\0';
   fputs(buf,stdout);

   pw(res);

}

void get_response(int src, int num, double * res) {

   char buf[2048];
   char * pos = buf;
   char * nextpos = NULL;

   int count = read(src,buf,sizeof(buf)-1);
   buf[count] = '\0';

   for (int i = 0; i < num && pos; ++i) {
      res[i] = strtod(pos,&nextpos);
      pos = nextpos;
   }

   pw(count);
}

int get_input() {


   sigset_t mask, before_mask;
   sigfillset(&mask);
   sigprocmask(SIG_SETMASK,&mask,&before_mask);

   int fd = fileno(stdin);

   struct termios before_termios;
   tcgetattr(fd,&before_termios);

   struct termios after = before_termios;
   after.c_cc[VMIN] = 1;
   after.c_cc[VTIME] = 0;
   after.c_lflag &= ~ICANON;
   after.c_lflag &= ~ECHO;

   tcsetattr(fd,TCSADRAIN,&after);

   char key;
   read(fd,&key,1);

   tcsetattr(fd,TCSADRAIN,&before_termios);
   sigprocmask(SIG_SETMASK,&before_mask,NULL);

   return key;
}

int main(int argc, char ** argv) {

   srand(time(NULL)*clock());

   if (rand()%11 == 7)
      printf("\033[31m!\n! Megumin is best girl !\n!\033[0m\n");

   /* notifications about the state the program was compiled in */

#ifdef DEBUG
   printf("\033[32mCompiled in debug mode\033[0m\n");
#endif
#ifdef INVERTM0
   printf("\033[36mCompiled with Motor0 inverted\033[0m\n");
#endif
#ifdef INVERTM1
   printf("\033[36mCompiled with Motor1 inverted\033[0m\n");
#endif
#ifdef INVERTDR
   printf("\033[36mCompiled with Drum inverted\033[0m\n");
#endif
#ifdef INVERTAR
   printf("\033[36mCompiled with Arm inverted\033[0m\n");
#endif
#ifdef NOARM
   printf("\033[36mCompiled with Arm Disabled\033[0m\n");
#endif

   /* get serial inputs to use during runtime */

#ifndef NOARM
   if (argc != 4) {
      printf("usage:\n%s [odrive0] [odrive1] [motor_controller]\n",argv[0]);
      printf("please pass serial bindings for all these values\n");
      exit(1);
   }
#else
   if (argc != 3) {
      printf("usage:\n%s [odrive0] [odrive1]\n",argv[0]);
      printf("please pass serial bindings for all these values\n");
      exit(1);
   }
#endif

   printf("connecting to motor0 at %s\n",argv[1]);
   int motor0 = open(argv[1],O_RDWR | O_NOCTTY);
   if (errno != 0) {
      printf("\033[31mconnection failed!\033[0m\n");
      perror("open");
      exit(1);
   }

   printf("connecting to motor1 at %s\n",argv[2]);
   int motor1 = open(argv[2],O_RDWR | O_NOCTTY);
   if (errno != 0) {
      printf("\033[31mconnection failed!\033[0m\n");
      perror("open");
      exit(1);
   }

#ifndef NOARM
   printf("connecting to controller at %s\n",argv[3]);
   int controller = open(argv[3],O_RDWR | O_NOCTTY);
   if (errno != 0) {
      printf("\033[31mconnection failed!\033[0m\n");
      perror("open");
      exit(1);
   }
#endif

   double motor_speed = 5;
   int drum_speed = 150;
   int step_speed = 25;
   int steps = 0;
   int count;

   int drum_spinning;

   int buf_len = 1024;

   char buf[buf_len];

   for ( ; ; ) {

      int key = get_input();

      drum_spinning = 0;

      switch(key) {
         case 'w':
            {
               snprintf(buf,buf_len,"v 0 %f\n", motor_speed * M0_MULT);
               pw(write(motor0,buf,strlen(buf)));
               snprintf(buf,buf_len,"v 0 %f\n", motor_speed * M1_MULT);
               pw(write(motor1,buf,strlen(buf)));

               break;
            }
         case 'a':
            {
               snprintf(buf,buf_len,"v 0 %f\n",-motor_speed * M0_MULT);
               pw(write(motor0,buf,strlen(buf)));
               snprintf(buf,buf_len,"v 0 %f\n", motor_speed * M1_MULT);
               pw(write(motor1,buf,strlen(buf)));

               break;
            }
         case 's':
            {
               snprintf(buf,buf_len,"v 0 %f\n",-motor_speed * M0_MULT);
               pw(write(motor0,buf,strlen(buf)));
               snprintf(buf,buf_len,"v 0 %f\n",-motor_speed * M1_MULT);
               pw(write(motor1,buf,strlen(buf)));

               break;
            }
         case 'd':
            {
               snprintf(buf,buf_len,"v 0 %f\n", motor_speed * M0_MULT);
               pw(write(motor0,buf,strlen(buf)));
               snprintf(buf,buf_len,"v 0 %f\n",-motor_speed * M1_MULT);
               pw(write(motor1,buf,strlen(buf)));

               break;
            }
         case 'i':
            {
               motor_speed += 1;
               printf("m\033[2J\033[H motor speed is now %f\n",motor_speed);

               break;
            }
         case 'o':
            {
               motor_speed -= 1;
               printf("\033[2J\033[H motor speed is now %f\n",motor_speed);

               break;
            }
         case 'r':
            {
#ifndef NOARM
               /*
               double curr;
               snprintf(buf,buf_len,"GET_ARM\n");
               pw(write(controller,buf,strlen(buf)));
               get_response(controller,1,&curr);
               int next = curr + 10 * AR_MULT;
               snprintf(buf,buf_len,"SET_ARM %d\n",next);
               pw(write(controller,buf,strlen(buf)));
               */

               steps += step_speed * AR_MULT;
               snprintf(buf,buf_len,"SET_ARM %d\n",steps);
               pw(write(controller,buf,strlen(buf)));
#endif

               break;
            }
         case 'f':
            {
#ifndef NOARM
               /*
               double curr;
               snprintf(buf,buf_len,"GET_ARM\n");
               pw(write(controller,buf,strlen(buf)));
               get_response(controller,1,&curr);
               int next = curr - 10 * AR_MULT;
               snprintf(buf,buf_len,"SET_ARM %d\n",next);
               pw(write(controller,buf,strlen(buf)));
               */

               steps -= step_speed * AR_MULT;
               snprintf(buf,buf_len,"SET_ARM %d\n",steps);
               pw(write(controller,buf,strlen(buf)));

               break;
            }
         case 'q':
            {
               drum_spinning = 1;
               snprintf(buf,buf_len,"SET_DRUM %d\n", drum_speed * DR_MULT);
               pw(write(controller,buf,strlen(buf)));

               /*
               snprintf(buf,buf_len,"echo -ne \"SET_DRUM %d\\n\"", drum_speed * DR_MULT);
               system(buf);
               */

#endif
               break;
            }
         case 'e':
            {
#ifndef NOARM
               drum_spinning = 1;
               snprintf(buf,buf_len,"SET_DRUM %d\n",-drum_speed * DR_MULT);
               pw(write(controller,buf,strlen(buf)));

               /*
               snprintf(buf,buf_len,"echo -ne \"SET_DRUM %d\\n\"", -drum_speed * DR_MULT);
               system(buf);
               */

#endif
               break;
            }
         case 'k':
            {
               snprintf(buf,buf_len,"v 0 0\n");
               pw(write(motor0,buf,strlen(buf)));
               pw(write(motor1,buf,strlen(buf)));

               printf("exiting...\n");
               goto cleanup;

               break;
            }
         case 'p':
            {
               printf("\033[2J\033[H\n");
#ifndef NOARM
               snprintf(buf,buf_len,"STATUS\n");
               pw(write(controller,buf,strlen(buf)));
               print_response(controller);
#endif
               double motors[2];
               snprintf(buf,buf_len,"f 0\n");
               pw(write(motor0,buf,strlen(buf)));
               get_response(motor0,2,motors);
               printf("Motor 0: [ pos: %lf, vel: %lf ]\n",motors[0],motors[1]);
               pw(write(motor1,buf,strlen(buf)));
               get_response(motor1,2,motors);
               printf("Motor 1: [ pos: %lf, vel: %lf ]\n",motors[0],motors[1]);

               break;
            }
         case 'c':
            {
               snprintf(buf,buf_len,"sc\n");
               pw(write(motor0,buf,strlen(buf)));
               pw(write(motor1,buf,strlen(buf)));

               break;
            }
         case 'x':
            {
               snprintf(buf,buf_len,"sr\n");
               pw(write(motor0,buf,strlen(buf)));
               pw(write(motor1,buf,strlen(buf)));

               printf("\033[2J\033[H\n");
               printf("Reboot started - waiting 20s\n");

               close(motor0);
               close(motor1);

               for (int i = 0; i < 20; ++i) {
                  sleep(1);
                  printf("\033[2J\033[H\n");
                  printf("Rebooting - waiting %ds\n",19 - i);
               }

               motor0 = open(argv[1],O_RDWR | O_NOCTTY);
               if (errno != 0) {
                  printf("\033[31mconnection failed!\033[0m\n");
                  perror("open");
                  exit(1);
               }

               motor1 = open(argv[2],O_RDWR | O_NOCTTY);
               if (errno != 0) {
                  printf("\033[31mconnection failed!\033[0m\n");
                  perror("open");
                  exit(1);
               }

               printf("\033[2J\033[H\n");
               printf("Reboot finished\n");

               break;
            }
         case ' ':
            {
#ifndef NOARM
               if (!drum_spinning) {
                  snprintf(buf,buf_len,"SET_DRUM 0\n");
                  pw(write(controller,buf,strlen(buf)));
               }
#endif
            }
         default:
            {
               snprintf(buf,buf_len,"v 0 0\n");
               pw(write(motor0,buf,strlen(buf)));
               pw(write(motor1,buf,strlen(buf)));

               break;
            }
      }

   }

cleanup:

   close(motor0);
   close(motor1);
#ifndef NOARM
   close(controller);
#endif

   return 0;
}
