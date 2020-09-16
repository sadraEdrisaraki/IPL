CFLAGS =-std=c11 -pedantic -Wall -Wvla -Werror -D_POSIX_C_SOURCE

exo1: check.o fork.o exo1.o
	gcc $(CFLAGS) -o exo1 check.o fork.o exo1.o
	
exo1.o: fork.h exo1.c
	gcc $(CFLAGS) -c exo1.c 

check.o: check.h check.c 
	gcc $(CFLAGS) -c check.c 

fork.o: check.h fork.h fork.c 
	gcc $(CFLAGS) -c fork.c 

clean:
	rm -f *.o
	rm -f exo1