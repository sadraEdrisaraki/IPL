CC=gcc
CCFLAGS=-D_DEFAULT_SOURCE -std=c11 -pedantic -Wvla -Wall -Werror

all: server client 

server : server.o check.o fork.o
	$(CC) $(CCFLAGS) -o server server.o check.o fork.o
server.o: server.c 
	$(CC) $(CCFLAGS) -c server.c

client : client.o check.o
	$(CC) $(CCFLAGS) -o client client.o check.o
client.o: client.c 
	$(CC) $(CCFLAGS) -c client.c

fork.o : fork.c 
	$(CC) $(CCFLAGS) -c fork.c

check.o : check.h check.c
	$(CC) $(CCFLAGS) -c check.c

clean : 
	rm -f server client *.o
	clear
