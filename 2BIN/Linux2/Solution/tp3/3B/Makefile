CFLAGS =-std=c11 -pedantic -Wall -Wvla -Werror

3B : pgmInscription.o
	gcc $(CFLAGS) -o 3B pgmInscription.o

pgmInscription.o : pgmInscription.c
	gcc $(CFLAGS) -c pgmInscription.c

clean :
	rm *.o
	rm 3B
