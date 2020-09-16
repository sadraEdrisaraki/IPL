CFLAGS =-std=c11 -pedantic -Wall -Wvla -Werror -D_POSIX_C_SOURCE

ex3A: check.o fork.o ex3A.o
	cc $(CFLAGS) -o ex3A check.o fork.o ex3A.o
	
check.o: check.h check.c 
	cc $(CFLAGS) -c check.c 

fork.o: check.h fork.h fork.c 
	cc $(CFLAGS) -c fork.c 

# for dev purpose
clear:
	clear
	
clean:
	rm -f *.o
	rm -f ex3A

dev: clear clean ex3A
	./ex3A
