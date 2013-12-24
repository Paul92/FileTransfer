#include<stdio.h>
#include<strings.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

#include<pthread.h>

#include "error.h"
#include "ftransLib.h"

int serverFileTransfer(int port, char* filename){

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0)
        errorOpeningSocket();
    
    struct sockaddr_in serv_addr, cli_addr;
    memset((char*) &serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;


    if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        errorOnBinding();

    listen(sockfd, 5);

    socklen_t cilen = sizeof(cli_addr);

    pthread_t newThread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    int noOfChilds = 0;

    while(1){
        int newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &cilen);
        noOfChilds++;

        struct fileWriteArgs args;
        args.sockfd = newsockfd;
        args.childNumber = noOfChilds;

        if(newsockfd < 0)
            errorOnAccept();

        pthread_create(&newThread, &attr, &fileWrite, &args);

    }

    pthread_attr_destroy(&attr);

    return 0;
}

int main(int argc, char** argv){
    serverFileTransfer(atoi(argv[1]), argv[2]);
    return 0;
}
