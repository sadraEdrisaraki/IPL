CFLAGS=-D_OPEN_C_SOURCE -D_DEFAULT_SOURCE -std=c11 -pedantic -Wall -Wvla -Werror
EXO=client
EXO2=serveur

all: $(EXO) $(EXO2)

$(EXO):  utils.o $(EXO).o
	cc $(CFLAGS) -o $(EXO) $(EXO).c utils.o  

$(EXO2):  utils.o $(EXO2).o
	cc $(CFLAGS) -o $(EXO2) $(EXO2).c utils.o  

$(EXO).o: utils.h $(EXO).c
	cc $(CFLAGS) -c $(EXO).c 

$(EXO2).o: utils.h $(EXO2).c
	cc $(CFLAGS) -c $(EXO2).c 

utils.o: utils.h utils.c 
	cc $(CFLAGS) -c utils.c 

# for dev purpose
clear:
	clear
	
clean:
	rm -f *.o
	rm -f $(EXO)
	rm -f $(EXO2)
	ipcrm -a