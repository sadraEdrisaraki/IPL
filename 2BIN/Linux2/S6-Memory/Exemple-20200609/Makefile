CFLAGS=-D_OPEN_C_SOURCE -D_SVID_SOURCE -std=c11 -pedantic -Wall -Wvla -Werror

all: semex1 shmex1

semex1: utils.h  utils.o semex1.c
	cc $(CFLAGS) -o semex1 semex1.c utils.o  

shmex1: utils.h  utils.o shmex1.c
	cc $(CFLAGS) -o shmex1 shmex1.c utils.o  

utils.o: utils.h utils.c 
	cc $(CFLAGS) -c utils.c 

# for dev purpose
clear:
	clear
	
clean:
	rm -f *.o
	rm -f shmex1
	rm -f semex1
	ipcrm -a

dev1: all
	./shmex1
	ipcs
	rm -f *.o
	
dev2: all
	./semex1
	ipcs
	rm -f *.o