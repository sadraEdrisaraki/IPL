CC=gcc
CCFLAGS=-std=c11 -pedantic -Wvla -Wall -Werror -DEFAULT_SOURCE

exo2 : exo2.o check.o
	$(CC) $(CCFLAGS) -o exo2 exo2.o check.o
exo2.o: exo2.c check.h
	$(CC) $(CCFLAGS) -c exo2.c

check.o : check.h check.c
	$(CC) $(CCFLAGS) -c check.c

clear :
		clear

clean :
	rm -f *.o
	rm -f exo2
	rm -f client
