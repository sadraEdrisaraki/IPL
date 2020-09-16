CFLAGS=-std=c11 -pedantic -Wall -Wvla -Werror -D_POSIX_C_SOURCE
EXO=client

$(EXO): check.o utils.o $(EXO).o
	gcc $(CFLAGS) -o $(EXO) check.o utils.o $(EXO).o

$(EXO).o: check.h utils.h $(EXO).c
	gcc $(CFLAGS) -c $(EXO).c

check.o: check.h check.c
	gcc $(CFLAGS) -c check.c

utils.o: check.h utils.h utils.c
	gcc $(CFLAGS) -c utils.c

clean:
	rm -f $(EXO)
	rm -f *.o