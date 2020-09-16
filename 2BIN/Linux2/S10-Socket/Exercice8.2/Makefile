CC=gcc
CCFLAGS=-std=c11 -pedantic -Wvla -Wall -Werror -DEFAULT_SOURCE

all: client

client : client.o check.o utils.o
	$(CC) $(CCFLAGS) -o client client.o check.o utils.o
	
client.o: client.c
	$(CC) $(CCFLAGS) -c client.c

check.o : check.h check.c
	$(CC) $(CCFLAGS) -c check.c

utils.o : utils.h utils.c
	$(CC) $(CCFLAGS) -c utils.c

clean :
	rm *.o
	rm client
