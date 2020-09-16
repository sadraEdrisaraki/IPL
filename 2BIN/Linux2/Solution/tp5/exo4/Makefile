CFLAGS =-D_POSIX_C_SOURCE=199309L -std=c11 -pedantic -Wall -Wvla -Werror

NAME = exo4

$(NAME): utils.o $(NAME).o
	gcc $(CFLAGS) -o $(NAME) utils.o $(NAME).o
	
$(NAME).o: utils.h $(NAME).c
	gcc $(CFLAGS) -c $(NAME).c 

utils.o: utils.h utils.c 
	gcc $(CFLAGS) -c utils.c 

# for dev purpose
clear:
	clear
	
clean:
	rm -f *.o
	rm -f $(NAME)

dev: clear clean $(NAME)
	./$(NAME)
