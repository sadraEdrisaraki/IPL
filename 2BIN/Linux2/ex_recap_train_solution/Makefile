CFLAGS =-D_DEFAULT_SOURCE -std=c11 -pedantic -Wall -Wvla -Werror

train : train.o check.o
	gcc $(CFLAGS) -o train train.o check.o

train.o: train.c check.h
	gcc $(CFLAGS) -c train.c

check.o: check.h check.c
	gcc $(CFLAGS) -c check.c

clean:
	rm *.o
	rm train