CC=gcc
CCFLAGS=-D_DEFAULT_SOURCE -std=c11 -pedantic -Wvla -Wall -Werror

all: server client

server : server.o utils.o communication.o
	$(CC) $(CCFLAGS) -o server server.o utils.o communication.o

server.o: server.c communication.h
	$(CC) $(CCFLAGS) -c server.c

client : client.o utils.o communication.o
	$(CC) $(CCFLAGS) -o client client.o utils.o communication.o

client.o: client.c communication.h
	$(CC) $(CCFLAGS) -c client.c

utils.o : utils.h utils.c
	$(CC) $(CCFLAGS) -c utils.c

communication.o : communication.h communication.c
	$(CC) $(CCFLAGS) -c communication.c

clean : 
		rm -f client server
		rm -f *.o
		clear