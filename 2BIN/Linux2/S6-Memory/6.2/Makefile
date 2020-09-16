CFLAGS=-D_OPEN_C_SOURCE -D_SVID_SOURCE -std=c11 -pedantic -Wall -Wvla -Werror

all: famille1

famille1: utils.h  utils.o famille1.c
	cc $(CFLAGS) -o famille1 famille1.c utils.o  

utils.o: utils.h utils.c 
	cc $(CFLAGS) -c utils.c 

# for dev purpose
clear:
	clear
	
clean:
	rm -f *.o
	rm -f famille1
	ipcrm -a

dev1: all
	./famille1
	ipcs
	rm -f *.o
	
dev2: all
	./famille1
	ipcs
	rm -f *.o