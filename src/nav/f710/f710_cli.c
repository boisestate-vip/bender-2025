
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

   while (!interrupted) {

      read(controller,&recved,sizeof(long));

      write(connfd,&recved,sizeof(long));

   }

   close(controller);
   close(connfd);

}
