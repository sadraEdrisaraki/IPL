CFLAGS =-D_POSIX_C_SOURCE=199309L -D_SVID_SOURCE -std=c11 -pedantic -Wall -Wvla -Werror

PGM = dist_create_ipc dist_delete_ipc distributeur ecran

all: $(PGM)

ecran: utils.o ecran.c gen.h
	gcc $(CFLAGS) -o ecran ecran.c utils.o 

distributeur: utils.o distributeur.c gen.h
	gcc $(CFLAGS) -o distributeur distributeur.c utils.o 

dist_create_ipc: utils.o dist_create_ipc.c gen.h
	gcc $(CFLAGS) -o dist_create_ipc dist_create_ipc.c utils.o 

dist_delete_ipc: utils.o dist_delete_ipc.c gen.h
	gcc $(CFLAGS) -o dist_delete_ipc dist_delete_ipc.c utils.o 

utils.o: utils.h utils.c 
	gcc $(CFLAGS) -c utils.c 

# for dev purpose
clear:
	clear
	
clean:
	rm -f *.o
	rm -f $(PGM)
