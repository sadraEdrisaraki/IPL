CFLAGS=-std=c11 -pedantic -Wall -Wvla -Werror -D_POSIX_C_SOURCE
EXO=3A

$(EXO): check.o fork.o $(EXO).o
	gcc $(CFLAGS) -o $(EXO) check.o fork.o $(EXO).o

$(EXO).o: check.h fork.h $(EXO).c
	gcc $(CFLAGS) -c $(EXO).c

check.o: check.h check.c
	gcc $(CFLAGS) -c check.c

fork.o: check.h fork.h fork.c
	gcc $(CFLAGS) -c fork.c

clean:
	rm -f $(EXO)
	rm -f *.o