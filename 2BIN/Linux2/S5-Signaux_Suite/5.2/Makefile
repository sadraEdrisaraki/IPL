CFLAGS =-std=c11 -pedantic -Wall -Wvla -Werror -D_POSIX_C_SOURCE

ex2: utils.o ex2.o
	cc $(CFLAGS) -o ex2 utils.o ex2.o
	
utils.o: utils.h utils.c 
	cc $(CFLAGS) -c utils.c 

# for dev purpose
clear:
	clear
	
clean:
	rm -f *.o
	rm -f ex2

dev: clear clean ex2
	./ex2
