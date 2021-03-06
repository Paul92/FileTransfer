#include "error.h"
#include<stdio.h>

void errorOpeningSocket(){
	printf("Error opening socket");
}

void errorOnBinding(){
	printf("Error on binding");
}

void errorOnAccept(){
	printf("Error on accept");
}

void errorWritingOnSocket(){
	printf("Error writing on socket");
}

void errorConnecting(){
	printf("Error connecting");
}

void noServerFound(){
	printf("No server found");
}

void errorOpeningFile(){
    printf("Can't open file");
}

void errorReadingFromFile(){
    printf("Can't read from file");
}

void errorReadingFromSocket(){
    printf("Can't read from socket");
}

void errorBadFileName(){
    printf("Bad file name");
}
