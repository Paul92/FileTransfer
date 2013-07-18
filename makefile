all: server client
error: error.c
	gcc -Wall -O1 -c -lm error.c -o error.o
ftransLib: ftransLib.c
	gcc -Wall -O1 -c -lm ftransLib.c -o ftransLib.o
client: ftransLib.o error.o client.c
	gcc -Wall -O1 -c -lm client.c -o client.o
	gcc -Wall -O1 -lm error.o client.o ftransLib.o -o client
server: ftransLib.o error.o server.c
	gcc -Wall -O1 -c -lm server.c -o server.o
	gcc -Wall -O1 -lm error.o server.o ftransLib.o -o server

