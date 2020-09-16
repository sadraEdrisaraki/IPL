CC=gcc
CCFLAGS=-D_DEFAULT_SOURCE -std=c11 -pedantic -Wvla -Wall -Werror

all: exempleServeurSocket exempleClientSocket

exempleServeurSocket : 	exempleServeurSocket.o 
						$(CC) $(CCFLAGS) -o exempleServeurSocket exempleServeurSocket.o
exempleServeurSocket.o: exempleServeurSocket.c 
						$(CC) $(CCFLAGS) -c exempleServeurSocket.c

exempleClientSocket: 	exempleClientSocket.o 
						$(CC) $(CCFLAGS) -o exempleClientSocket exempleClientSocket.o

exempleClientSocket.o:  exempleClientSocket.c
						$(CC) $(CCFLAGS) -c exempleClientSocket.c

clean : 
	rm -f exempleServeurSocket exempleClientSocket *.o
	clear
