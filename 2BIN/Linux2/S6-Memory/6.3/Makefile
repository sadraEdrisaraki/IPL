CFLAGS=-D_OPEN_C_SOURCE -D_SVID_SOURCE -std=c11 -pedantic -Wall -Wvla -Werror

all: distributeur ecran admin

distributeur: utils.h  utils.o distributeur.c
	cc $(CFLAGS) -o distributeur distributeur.c utils.o  

ecran: utils.h  utils.o ecran.c
	cc $(CFLAGS) -o ecran ecran.c utils.o  

admin: utils.h  utils.o admin.c
	cc $(CFLAGS) -o admin admin.c utils.o  


utils.o: utils.h utils.c 
	cc $(CFLAGS) -c utils.c 

# for dev purpose
clear:
	clear
	
clean:
	rm -f *.o
	rm -f distributeur
	rm -f ecran
	rm -f admin
	ipcrm -a

dev1: all
	./distributeur
	ipcs
	rm -f *.o
	
dev2: all
	./ecran
	ipcs
	rm -f *.o

dev2: all
	./admin
	ipcs
	rm -f *.o