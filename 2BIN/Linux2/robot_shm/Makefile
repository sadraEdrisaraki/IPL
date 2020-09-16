CFLAGS=-D_OPEN_C_SOURCE -D_DEFAULT_SOURCE -std=c11 -pedantic -Wall -Wvla -Werror

CONTROLLER=controller
ROBOT_CREATE_IPC=robot_create_ipc
ROBOT_DELETE_IPC=robot_delete_ipc

all : $(CONTROLLER) $(ROBOT_CREATE_IPC) $(ROBOT_DELETE_IPC) 

$(CONTROLLER): gen.h utils.h utils.o $(CONTROLLER).o
	cc $(CFLAGS) -o $(CONTROLLER) $(CONTROLLER).o utils.o 
	
$(ROBOT_CREATE_IPC): gen.h utils.h utils.o $(ROBOT_CREATE_IPC).c
	cc $(CFLAGS) -o $(ROBOT_CREATE_IPC) $(ROBOT_CREATE_IPC).c utils.o

$(ROBOT_DELETE_IPC): gen.h utils.h utils.o $(ROBOT_DELETE_IPC).c
	cc $(CFLAGS) -o $(ROBOT_DELETE_IPC) $(ROBOT_DELETE_IPC).c utils.o

utils.o: utils.h utils.c 
	cc $(CFLAGS) -c utils.c 

# for dev purpose
clear:
	clear
	
clean:
	rm -f *.o

