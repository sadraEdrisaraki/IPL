CFLAGS =-D_DEFAULT_SOURCE -std=c11 -pedantic -Wall -Wvla -Werror
EXO = train

$(EXO) : check.o $(EXO).o
	gcc $(CFLAGS) -o $(EXO) check.o $(EXO).o

$(EXO).o : check.h $(EXO).c
	gcc $(CFLAGS) -c $(EXO).c

check.o : check.h check.c
	gcc $(CFLAGS) -c check.c

clean:
	rm -f $(EXO)
	rm -f *.o