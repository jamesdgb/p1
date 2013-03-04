#include <stdio.h>
#include <stdlib.h>
#include "socket.h"

void printUsage(){
   printf("usage : hello [-c | -s | hostname] \n");
   printf("   -c : start client\n");
   printf("   -s : start server\n");
}


int main(int argc, char **argv)
{
    char* defaultServer="google.com";

    switch(argc)
    {
        case 0:
             return -1;
             break;
        case 1:
             socketCreation(defaultServer);
             break;
        case 2:
             if(strcmp(argv[1],"-s")==0){
                 socketServer();
             }else if(strcmp(argv[1],"-c")==0){
                 socketClient("127.0.0.1");
             }else if(strcmp(argv[1],"-h")==0){
                 printUsage();
             }else if(argv[1][0]=='-'){
                 printf("Invalid option\n");
                 printUsage();
             }else{
                 socketCreation(argv[1]);
             }
             break;
        default:
             printf("invalid option\n");
             printUsage();
             return -1;
    }
    return 0;
}
