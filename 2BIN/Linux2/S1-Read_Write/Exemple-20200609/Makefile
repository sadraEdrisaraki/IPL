CFLAGS=-std=c11 -pedantic -Wall -Wvla -Werror

ex1: ex1.o 
	gcc $(CFLAGS) -o ex1 ex1.o

ex1.o: ex1.c 
	gcc $(CFLAGS) -c ex1.c

clean:
	rm -f *.o
	rm -f ex1
	rm -f test
