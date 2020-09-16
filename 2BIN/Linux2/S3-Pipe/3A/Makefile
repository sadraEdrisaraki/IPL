CFLAGS =-std=c11 -pedantic -Wall -Wvla -Werror

ex3B: check.o fork.o pgmInscription.o
	cc $(CFLAGS) -o ex3B check.o fork.o pgmInscription.o
	
pgmInscription.o: fork.h pgmInscription.c
	cc $(CFLAGS) -c pgmInscription.c 

check.o: check.h check.c 
	cc $(CFLAGS) -c check.c 

fork.o: check.h fork.h fork.c 
	cc $(CFLAGS) -c fork.c 

# for dev purpose
clear:
	clear
	
clean:
	rm -f *.o
	rm -f ex3B

dev: clear clean ex3B
	./ex3B
