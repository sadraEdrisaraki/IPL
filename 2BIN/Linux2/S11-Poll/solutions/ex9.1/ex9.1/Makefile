CC=gcc
CCFLAGS=-std=c11 -pedantic -Wvla -Wall -Werror -DEFAULT_SOURCE

all: clean clear server client

server : server.o check.o
	$(CC) $(CCFLAGS) -o server server.o check.o
server.o: server.c messages.h
	$(CC) $(CCFLAGS) -c server.c

client : client.o check.o
	$(CC) $(CCFLAGS) -o client client.o check.o
client.o: client.c messages.h
	$(CC) $(CCFLAGS) -c client.c

check.o : check.h check.c
	$(CC) $(CCFLAGS) -c check.c

clear :
		clear

clean :
	rm -f *.o
	rm -f server
	rm -f client
