#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<string.h>

#include<unistd.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

#include "error.h"
#include "ftransLib.h"

int clientFileTransfer(char *ip, int port, char* filename){
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
        errorOpeningSocket();

    struct hostent* server = gethostbyname(ip);
    if(server == NULL)
        noServerFound();

    struct sockaddr_in serv_addr;
    memset((char*)&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    bcopy((char*) server -> h_addr, (char*) &serv_addr.sin_addr.s_addr, server -> h_length);

    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        errorConnecting();

    fileRead(filename, sockfd);

    return 0;
}

int main(int argc, char** argv){
    clientFileTransfer(argv[1], atoi(argv[2]), argv[3]);
    return 0;
}
