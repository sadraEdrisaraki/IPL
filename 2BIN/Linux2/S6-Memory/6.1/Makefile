CFLAGS=-D_OPEN_C_SOURCE -D_SVID_SOURCE -std=c11 -pedantic -Wall -Wvla -Werror

all: radar dashboard

radar: utils.h  utils.o radar.c
	cc $(CFLAGS) -o radar radar.c utils.o 

dashboard: utils.h  utils.o dashboard.c
	cc $(CFLAGS) -o dashboard dashboard.c utils.o  	 

utils.o: utils.h utils.c 
	cc $(CFLAGS) -c utils.c 

# for dev purpose
clear:
	clear
	
clean:
	rm -f *.o
	rm -f radar
	rm -f dashboard
	ipcrm -a

dev1: all
	./radar
	ipcs
	rm -f *.o
	
dev2: all
	./dashboard
	ipcs
	rm -f *.o