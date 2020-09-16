CFLAGS =-std=c11 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE
EXO=exo2

$(EXO): check.o fork.o $(EXO).o
	gcc $(CFLAGS) -o $(EXO) check.o fork.o $(EXO).o
	
$(EXO).o: fork.h $(EXO).c
	gcc $(CFLAGS) -c $(EXO).c 

check.o: check.h check.c 
	gcc $(CFLAGS) -c check.c 

fork.o: check.h fork.h fork.c 
	gcc $(CFLAGS) -c fork.c 

clean:
	rm -f *.o
	rm -f $(EXO)