CFLAGS =-std=c11 -pedantic -Wall -Wvla -Werror

3A: check.o fork.o 3A.o
	cc $(CFLAGS) -o 3A check.o fork.o 3A.o
	
3A.o: fork.h 3A.c
	cc $(CFLAGS) -c 3A.c 

check.o: check.h check.c 
	cc $(CFLAGS) -c check.c 

fork.o: check.h fork.h fork.c 
	cc $(CFLAGS) -c fork.c 

# for dev purpose
clear:
	clear
	
clean:
	rm -f *.o
	rm -f 3A

dev: clear clean 3A
	./3A
