/* Used by server and client */
#define _POSIX_SOURCE

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>
/* struct sockaddr_in */
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "check.h"

#define SERVER_PORT 		9502
#define SERVER_IP		"127.0.0.1"  /* localhost */
#define MAX_PSEUDO 		256

#define INSCRIPTION_REQUEST  	10
#define INSCRIPTION_OK		11
#define INSCRIPTION_KO 		12
#define	PIERRE			13
#define PAPIER			14
#define CISEAUX			15


/* struct message used between server and client */
typedef struct {
	char MessageText[MAX_PSEUDO];
	int code;
} structMessage;
