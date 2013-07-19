#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sendfile.h>

#include "error.h"
#include "ftransLib.h"

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
    sprintf(size, "%d", fileSize);
    write(sockfd, size, 32);

    char *name = strrchr(filename, '/');
    if(name == NULL)
        name = filename;
    else
        name++;

    char fileNameSize = strlen(name)+1;
    write(sockfd, &fileNameSize, 1);  //WARNING! it works only for files
                                           //with at most 255 characters

    write(sockfd, name, strlen(name)+1);

    int n = 0; //total bytes read/written
    char buffer[BUFFER_SIZE];
    while(!feof(f)){
        int read = fread(buffer, 1, BUFFER_SIZE, f);
        if(read < 0)
            errorReadingFromFile();

        write(sockfd, buffer, read);

        n+=read;
        loader(n, fileSize, LOADER_LENGTH);
    }

    fclose(f);
}


void fileWrite(int sockfd){

    char sz[32];
    read(sockfd, sz, 32);
    int fileSize = atoi(sz);

    char fileNameSize;
    int readed = read(sockfd, &fileNameSize, 1);
    if(readed < 0)
        errorReadingFromSocket();
    else if(fileNameSize == 0)
        errorBadFileName();

    char filename[256];
    readed = read(sockfd, filename, fileNameSize);
    if(readed < 0)
        errorReadingFromSocket();

    FILE *f = fopen(filename, "wb");
    if(f == NULL){
        errorOpeningFile();
    }

    char buffer[BUFFER_SIZE];
    int n = 0;
    while(n < fileSize){
        readed = read(sockfd, buffer, BUFFER_SIZE);
        if(readed < 0)
            errorReadingFromSocket();

        write(fileno(f), buffer, readed);

        n += readed;
        loader(n, fileSize, LOADER_LENGTH);
    }

    fclose(f);

}

