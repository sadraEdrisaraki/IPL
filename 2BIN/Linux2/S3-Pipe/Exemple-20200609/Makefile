CFLAGS =-std=c11 -pedantic -Wall -Wvla -Werror

ex1: check.o fork.o ex1.o
	cc $(CFLAGS) -o ex1 check.o fork.o ex1.o
	
ex1.o: fork.h ex1.c
	cc $(CFLAGS) -c ex1.c 

check.o: check.h check.c 
	cc $(CFLAGS) -c check.c 

fork.o: check.h fork.h fork.c 
	cc $(CFLAGS) -c fork.c 

# for dev purpose
clear:
	clear
	
clean:
	rm -f *.o
	rm -f ex1

dev: clear clean ex1
	./ex1
