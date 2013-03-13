#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#include "socket.h"

#define WINDOW_WIDTH 80

void printNChar(int length,char c){
   int i;
   for(i=0;i<length;i++)
   {
      printf("%c",c);
   }
   printf("\n");
}

void printLineLength(int length){
   printNChar(length,'-');
}

void printLine(){
   printLineLength(WINDOW_WIDTH);
}

void socketCreation(char *serverName) 
{
    printLine();
    printf("%80s\n","STARTING SOCKET");
	SOCKET sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock == INVALID_SOCKET)
	{
	    perror("socket()");
	    exit(-1);
	}
	struct hostent *hostinfo = NULL;
    SOCKADDR_IN sin = { 0 }; /* initialise la structure avec des 0 */
    const char *hostname = serverName;

    hostinfo = gethostbyname(hostname); /* on récupère les informations de l'hôte auquel on veut se connecter */
    if (hostinfo == NULL) /* l'hôte n'existe pas */
    {
        fprintf (stderr, "Unknown host %s.\n", hostname);
        exit(EXIT_FAILURE);
    }

    printf("%s address is : %d.%d.%d.%d (%d oct)\n",hostinfo->h_name,
      hostinfo->h_addr[0],hostinfo->h_addr[1],hostinfo->h_addr[2],
      hostinfo->h_addr[3],hostinfo->h_length);
    sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr; /* l'adresse se trouve dans le champ h_addr de la structure hostinfo */
    sin.sin_port = htons(80); /* on utilise htons pour le port */
    sin.sin_family = AF_INET;

    if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
    {
        perror("connect()");
        exit(-2);
    }

    printf("%80s\n","ENDING SOCKET");
    printLine();
}


void socketServer()
{
   int listenfd=0, connfd=0;
   struct sockaddr_in serv_addr;

   char sendBuff[1025];
   time_t ticks;

   listenfd = socket(AF_INET, SOCK_STREAM,0);
   memset(&serv_addr, '0', sizeof(serv_addr));
   memset(sendBuff, '0', sizeof(sendBuff));

   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
   serv_addr.sin_port = htons(5000);

   bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));

   listen(listenfd,10);

   while(1)
   {
      connfd=accept(listenfd,(struct sockaddr*) NULL,NULL);
      ticks = time(NULL);
      snprintf(sendBuff,sizeof(sendBuff),"%.24s\r\n",ctime(&ticks));
      write(connfd,sendBuff,strlen(sendBuff));
      printf("Server sending --> %.24s\r\n",ctime(&ticks));
      close(connfd);
      sleep(1);
   }
}

   void socketClient(char *ipServer)
   {
      int sockfd = 0, n=0;
      char recvBuff[1024];
      struct sockaddr_in serv_addr;

      memset(recvBuff,'0',sizeof(recvBuff));
      if((sockfd=socket(AF_INET,SOCK_STREAM,0)) < 0)
      {
         printf("\n Error : Could not create socket \n");
      }
      memset(&serv_addr,'0',sizeof(serv_addr));

      serv_addr.sin_family = AF_INET;
      serv_addr.sin_port = htons(5000);

      if(inet_pton(AF_INET,ipServer, &serv_addr.sin_addr)<=0)
      {
         printf("\n inet_pton error occured\n");
      }

      if(connect(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
      {
         printf("\n Error : Connect Failed \n");
      }
      while((n=read(sockfd,recvBuff,sizeof(recvBuff)-1))>0)
      {
          recvBuff[n] = 0;
          printf("Client rceving <-- ");
          if(fputs(recvBuff, stdout) == EOF)
          {
             printf("\n Error : Fputs error\n");
          }
      }
      if( n < 0)
      {
          printf("\n Read error \n");
      }
   }
