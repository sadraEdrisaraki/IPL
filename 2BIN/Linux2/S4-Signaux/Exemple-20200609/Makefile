CFLAGS =-std=c11 -pedantic -Wall -Wvla -Werror -D_POSIX_C_SOURCE

exemple1: check.o fork.o exemple1.o
	gcc $(CFLAGS) -o exemple1 check.o fork.o exemple1.o
	
exemple1.o: fork.h exemple1.c
	gcc $(CFLAGS) -c exemple1.c 

check.o: check.h check.c 
	gcc $(CFLAGS) -c check.c 

fork.o: check.h fork.h fork.c 
	gcc $(CFLAGS) -c fork.c 

clean:
	rm -f *.o
	rm -f exemple1

