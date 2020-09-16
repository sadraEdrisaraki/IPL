CFLAGS =-D_POSIX_C_SOURCE=200809L -std=c11 -pedantic -Wall -Wvla -Werror

ex2B: check.o fork.o ex2B.o
	cc $(CFLAGS) -o ex2B check.o fork.o ex2B.o
	
ex2B.o: fork.h ex2B.c
	cc $(CFLAGS) -c ex2B.c 

check.o: check.h check.c 
	cc $(CFLAGS) -c check.c 

fork.o: check.h fork.h fork.c 
	cc $(CFLAGS) -c fork.c 

# for dev purpose
clear:
	clear
	
clean:
	rm -f *.o
	rm -f ex2B

dev: clear clean ex2B
	./ex2B