CFLAGS =-std=c11 -pedantic -Wall -Wvla -Werror -D_POSIX_C_SOURCE

all: exemple2

exemple2: check.o fork.o exemple2.o
	gcc $(CFLAGS) -o exemple2 check.o fork.o exemple2.o

exemple2.o: check.h fork.h exemple2.c
	gcc $(CFLAGS) -c exemple2.c

check.o: check.h check.c
	gcc $(CFLAGS) -c check.c

fork.o: check.h fork.h fork.c
	gcc $(CFLAGS) -c fork.c

clean:
	rm -f *.o
	rm -f exemple1 exemple2
