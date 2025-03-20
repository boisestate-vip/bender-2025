
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/select.h>

#ifdef DEBUG
#define print_written(x) printf("bytes written: %d\n",x)
#else
#define print_written(x) do { (void)x; } while (0)
#endif

#ifdef INVERT
#define conv(x) (-1*x*1.373)
#else
#define conv(x) (x*1.373)
#endif


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

   tcsetattr(fd,TCSADRAIN,&after);

   char key;
   read(fd,&key,1);

   tcsetattr(fd,TCSADRAIN,&before_termios);
   sigprocmask(SIG_SETMASK,&before_mask,NULL);

   return key;
}

int nonblock_write(int fd, char * str) {

   int len = strlen(str);
   int count = 0;

again:
   count = write(fd,str,len-count);

   if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR) {
      errno = 0;
      goto again;
   }

   print_written(count);
   return count;
}

int nonblock_read(int fd, char * buf) {

   int count = 0;

   fd_set wait;
   struct timeval timeout;

again:
   FD_ZERO(&wait);
   FD_SET(fd,&wait);
   timeout.tv_sec = 0; 
   timeout.tv_usec = 100000;

   select(fd+1,&wait,NULL,NULL,&timeout);

   count = read(fd,buf+count,1);

   if (count == 1 || errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR) {
      errno = 0;
      goto again;
   }

   print_written(count);
   return count;
}

int main(int argc, char ** argv) {

#ifdef DEBUG
   printf("\033[32mCompiled in debug mode\033[0m\n");
#endif
#ifdef INVERT
   printf("\033[34mCompiled in invert mode\033[0m\n");
#endif


   if (argc != 2) {
      printf("usage:\n%s [odrive tty]\n",argv[0]);
      exit(1);
   }

   int conn = open(argv[1],O_RDWR | O_NOCTTY | O_NONBLOCK);
   if (errno != 0) {
      perror("connection");
      exit(1);
   }

   double speed = 5;
   int count;

   char buf[128];

   float pos, vel;

   for ( ; ; ) {

      char key = get_input();

      switch (key) {
         case 'w':

            snprintf(buf,128,"v 0 %f\n",conv(speed));

            count = nonblock_write(conn,buf);

            snprintf(buf,128,"v 1 %f\n",conv(-speed));

            count = nonblock_write(conn,buf);

            break;
         case 'a':

            snprintf(buf,128,"v 0 %f\n",conv(-speed));

            count = nonblock_write(conn,buf);

            snprintf(buf,128,"v 1 %f\n",conv(-speed));

            count = nonblock_write(conn,buf);

            break;
         case 's':

            snprintf(buf,128,"v 0 %f\n",conv(-speed));

            count = nonblock_write(conn,buf);

            snprintf(buf,128,"v 1 %f\n",conv(speed));

            count = nonblock_write(conn,buf);

            break;
         case 'd':

            snprintf(buf,128,"v 0 %f\n",conv(speed));

            count = nonblock_write(conn,buf);

            snprintf(buf,128,"v 1 %f\n",conv(speed));

            count = nonblock_write(conn,buf);

            break;
         case 'i':

            speed += 1;

            printf("speed is now %f\n",conv(speed));

            break;
         case 'o':

            speed -= 1;

            printf("speed is now %f\n",conv(speed));

            break;
            /*
         case 'r':

            snprintf(buf,128,"f 0\n");

            count = nonblock_write(conn,buf);

            count = nonblock_read(conn,buf);

            sscanf(buf,"%f %f",&pos,&vel);
            printf("motor 0 position %f velocity %f\n",pos,vel);

            snprintf(buf,128,"f 1\n");

            count = nonblock_write(conn,buf);

            count = nonblock_read(conn,buf);

            sscanf(buf,"%f %f",&pos,&vel);
            printf("motor 1 position %f velocity %f\n",pos,vel);

            break;
            */
         case 'q':

            snprintf(buf,128,"v 0 0\n");

            count = nonblock_write(conn,buf);

            snprintf(buf,128,"v 1 0\n");

            count = nonblock_write(conn,buf);

            printf("exiting...\n");

            exit(1);

            break;

            break;
         default:

            snprintf(buf,128,"v 0 0\n");

            count = nonblock_write(conn,buf);

            snprintf(buf,128,"v 1 0\n");

            count = nonblock_write(conn,buf);

            break;
      }

   }

   close(conn);

   return 0;

}


