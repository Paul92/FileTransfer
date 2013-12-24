#define BUFFER_SIZE 1024
#define LOADER_LENGTH 20

struct fileWriteArgs{
    int childNumber;
    int sockfd;
};

void fileRead(char*, int);
void* fileWrite(void*);

