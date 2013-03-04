#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
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

void socketCreation(void)
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
    const char *hostname = "www.google.com";

    hostinfo = gethostbyname(hostname); /* on récupère les informations de l'hôte auquel on veut se connecter */
    if (hostinfo == NULL) /* l'hôte n'existe pas */
    {
        fprintf (stderr, "Unknown host %s.\n", hostname);
        exit(EXIT_FAILURE);
    }

    printf("%s address is : %d.%d.%d.%d (%d oct)\n",hostinfo->h_name,hostinfo->h_addr[0],hostinfo->h_addr[1],hostinfo->h_addr[2],hostinfo->h_addr[3],hostinfo->h_length);
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
