#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"
#include "ftransLib.h"

void itoa(int a, char buff[32]){
    int i = 0;
    char temp[32];
    while(a > 0){
        temp[i] = a%10 + '0';
        a /= 10;
        i++;
    }
    temp[i] = '\0';
    buff[i] = '\0';
    int size = --i;
    for(; i>=0; buff[size - i] = temp[i], i--);
}

void fileRead(char *filename, int sockfd){

    FILE *f = fopen(filename, "rb");
    
    if(f == NULL){
        errorOpeningFile();
        return;
    }

    fseek(f, 0, SEEK_END);
    int fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char size[32];
    itoa(fileSize, size);
    write(sockfd, size, 32);

    char buffer[BUFFER_SIZE];
    while(!feof(f)){
        int read = fread(buffer, 1, BUFFER_SIZE, f);
        write(sockfd, buffer, read);
        if(read < 0)
            errorWritingOnSocket();
    }

    fclose(f);
}


void fileWrite(char *filename, int sockfd){

    FILE *f = fopen(filename, "wb");

    if(f == NULL){
        errorOpeningFile();
        return;
    }

    char sz[32];
    read(sockfd, sz, 32);
    int size = atoi(sz);

    char buffer[BUFFER_SIZE];
    int n = 0;
    while(n < size){
        int readed = read(sockfd, buffer, BUFFER_SIZE);
        write(fileno(f), buffer, readed);
        printf("%d\n", n);
        n += readed;
    }

    fclose(f);

}

