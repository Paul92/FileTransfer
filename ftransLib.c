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

void loader(int val, int max, int size){

    static int lastPrinted = 0;

    int percent = (100.*val)/max;
    int count = ((float)percent * size) / 100;

    if(count == lastPrinted)
        return;

    lastPrinted = count;
    printf("\r[");

    int i;
    for(i = 0; i < count; i++)
        printf("#");
    for(; i < size; i++)
        printf(".");

    printf("] %d%%", percent);
    fflush(stdout);
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

    int n = 0; //total bytes read/written
    char buffer[BUFFER_SIZE];
    while(!feof(f)){
        int read = fread(buffer, 1, BUFFER_SIZE, f);
        if(read < 0)
            errorWritingOnSocket();

        write(sockfd, buffer, read);

        n += read;
        loader(n, fileSize, LOADER_LENGTH);

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
    int fileSize = atoi(sz);

    char buffer[BUFFER_SIZE];
    int n = 0;
    while(n < fileSize){
        int readed = read(sockfd, buffer, BUFFER_SIZE);
        write(fileno(f), buffer, readed);

        n += readed;
        loader(n, fileSize, LOADER_LENGTH);
    }

    fclose(f);

}

