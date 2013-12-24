CFLAGS = -Wall -O2 -lm
LIBS = -lpthread
CC = gcc

all: server client
error: error.c
	$(CC) $(CFLAGS) -c error.c -o error.o
ftransLib: ftransLib.c
	$(CC) $(CFLAGS) -c ftransLib.c -o ftransLib.o
client: ftransLib.o error.o client.c
	$(CC) $(CFLAGS) -c client.c -o client.o
	$(CC) $(CFLAGS) error.o client.o ftransLib.o -o client
server: ftransLib.o error.o server.c
	$(CC) $(CFLAGS) -c server.c -o server.o
	$(CC) $(CFLAGS) error.o server.o ftransLib.o -o server $(LIBS)
clean:
	rm *.o
