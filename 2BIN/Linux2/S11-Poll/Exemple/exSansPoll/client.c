/* Used by server and client */
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
/* struct sockaddr_in */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "check.h"

#define MESSAGE_SIZE 8192


int initSocketClient(char ServerIP[16], int Serverport)
{
  	int sockfd;
  	int ret;
  	struct sockaddr_in addr;
  	sockfd = socket(AF_INET, SOCK_STREAM, 0);
  	checkNeg(sockfd,"socket client creation error");

	memset(&addr,0,sizeof(addr)); /* en System V */
	addr.sin_family = AF_INET;
	addr.sin_port = htons(Serverport);
	inet_aton(ServerIP,&addr.sin_addr);
	ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
	checkNeg(ret,"connect client error");
	
    return sockfd;
}


int main(int argc, char** argv)
{

	int sockfd;
	int ret;
	char msg [MESSAGE_SIZE];


	if (argc != 3)
	{
		printf("%s\n", "Usage argv[0] ServerIP ServerPort");
		exit(1);
	}

	// initClient before read keyboard ... not a good idea
	sockfd = initSocketClient(argv[1], atoi(argv[2]));

	printf("Bienvenue dans le programe vache - Entrez votre pseudo\n");

	ret = read(0,msg,256);
	checkNeg(ret,"read client error");	
	
	ret = write(sockfd,msg,sizeof(msg));
	checkNeg(ret,"write client error");	

	/* wait server response */
	ret = read(sockfd,msg,sizeof(msg));
	checkNeg(ret,"read client error");

	//printf("taille msg : %li\n", strlen(msg));
	printf("Réponse du serveur : \n");
	printf ("%s\n", msg);		
		
	
	
	close(sockfd);		

	return 0;
}




