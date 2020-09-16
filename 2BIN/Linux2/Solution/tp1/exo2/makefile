CFLAGS=-std=c11 -pedantic -Wall -Wvla -Werror

lireEtEcrire: lireEtEcrire.o
	gcc $(CFLAGS) -o lireEtEcrire lireEtEcrire.o

lireEtEcrire.o: lireEtEcrire.c
	gcc $(CFLAGS) -c lireEtEcrire.c

clean:
	rm lireEtEcrire
	rm *.o