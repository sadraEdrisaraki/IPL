#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

/* Used by server and client */
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
/* struct sockaddr_in */
#include <netinet/in.h>
#include <arpa/inet.h>

#include "utils.h"


#define MESSAGE_SIZE 		1024

#define LS				  	100
#define GET_INDEX			200
#define UNKNOW_COMMAND 		500


/* struct message used between server and client */
typedef struct {
	char MessageText[MESSAGE_SIZE];
	int code;
} structMessage;

int initSocketClient(char serverIP[16], int serverPort);

int initSocketServer(int port);

#endif
