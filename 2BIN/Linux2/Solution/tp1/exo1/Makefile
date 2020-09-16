CFLAGS=-std=c11 -pedantic -Wall -Wvla -Werror

lire: lire.o
	gcc $(CFLAGS) -o lire lire.o

lire.o: lire.c
	gcc $(CFLAGS) -c lire.c

clean: 
	rm lire
	rm *.o
