CFLAGS=-std=c11 -pedantic -Wall -Wvla -Werror -D_POSIX_C_SOURCE  #-D_DEFAULT_SOURCE

#all: ex4.1a ex4.1b ex4.1c

#ex4.1a: check.o ex4.1a.o
#	gcc $(CFLAGS) -o ex4.1a check.o ex4.1a.o

#ex4.1a.o: check.h ex4.1a.c
#	gcc $(CFLAGS) -c ex4.1a.c 

#ex4.1b: check.o ex4.1b.o
#	gcc $(CFLAGS) -o ex4.1b check.o ex4.1b.o

#ex4.1b.o: check.h ex4.1b.c
#	gcc $(CFLAGS) -c ex4.1b.c 

ex4.1c: check.o fork.o ex4.1c.o
	gcc $(CFLAGS) -o ex4.1c check.o fork.o ex4.1c.o

ex4.1c.o: check.h fork.h ex4.1c.c
	gcc $(CFLAGS) -c ex4.1c.c 

check.o: check.h check.c 
	gcc $(CFLAGS) -c check.c 

fork.o: check.h fork.h fork.c 
	gcc $(CFLAGS) -c fork.c 

clean:
	rm -f *.o
	rm -f ex4.1?
