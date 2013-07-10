#include<stdio.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

int serverFileTransfer(int port){

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0)
        errorOpeningSocket();
    
    struct sockaddr_in serv_addr, cli_addr;
    bzero((char*) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = port;
    serv_addr.sin_addr.s.addr = INADDR_ANY;

    if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        errorOnBinding();

    listen(sockfd, 5);

    cilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &cilen);
    if(newsockfd < 0)
        errorOnAccept();

    char buffer[1000];
    bzero(buffer, sizeof(buffer));

    int n = read(newsockfd, buffer, sizeof(buffer));
    printf("MESSAGE: %s", buffer);

    return 0;
}

int main(int argc, char** argv){
    serverFileTransfer(argv[0], argv[1]);
    return 0;
}
