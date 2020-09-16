CFLAGS =-std=c11 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE

all: exercice2

exercice2: check.o fork.o exercice2.o
	gcc $(CFLAGS) -o exercice2 check.o fork.o exercice2.o

exercice2.o: check.h fork.h exercice2.c
	gcc $(CFLAGS) -c exercice2.c

check.o: check.h check.c
	gcc $(CFLAGS) -c check.c

fork.o: check.h fork.h fork.c
	gcc $(CFLAGS) -c fork.c

clean:
	rm -f *.o
	rm -f exemple1 exercice2
