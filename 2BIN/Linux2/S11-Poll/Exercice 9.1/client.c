#include "messages.h"


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
	addr.sin_addr.s_addr = inet_addr(ServerIP);
	ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
	checkNeg(ret,"connect client error");
	
    	return sockfd;
}


int main(int argc, char** argv)
{

	char pseudo[MAX_PSEUDO];
	int sockfd;
	int ret;

	structMessage msg;
	char c; // ne fonctionne pas avec l'entier int c
			
		
	/* retrieve player name */
	printf("Bienvenue dans le programe d'inscription au serveur de jeu\n");
	printf("Pour participer entrez votre nom :\n");
	ret = read(0,pseudo,MAX_PSEUDO);
	checkNeg(ret,"read client error");
	pseudo[ret-1] = '\0';
	strcpy(msg.MessageText,pseudo);
	msg.code = INSCRIPTION_REQUEST;	

	sockfd = initSocketClient(SERVER_IP, SERVER_PORT);

	ret = write(sockfd,&msg,sizeof(msg));
	checkNeg(ret,"write client error");	

	/* wait server response */
	ret = read(sockfd,&msg,sizeof(msg));
	checkNeg(ret,"read client error");


	if (msg.code == INSCRIPTION_OK)
	{
		printf("Réponse du serveur : Inscription acceptée\n");		
		
	
	}
	if (msg.code == INSCRIPTION_KO)
	{
		printf("Réponse du serveur : Inscription refusée\n");	
		exit(0);	
	}

	printf("Envoyez P pour Papier, C pour Ciseaux, R pour Pierre\n");
	ret = read(0,&c,1);
	checkNeg(ret,"read client error");

	char P = 'P';
	char C = 'C';
	char R = 'R';

	printf("%d : %d\n", c, P);

	if (c == P)
	{
		msg.code = PAPIER;
	}
	if (c == C)
	{
		msg.code = CISEAUX;
	}
	if (c == R)
	{
		msg.code = PIERRE;
	}
	ret = write(sockfd,&msg,sizeof(msg));
	checkNeg(ret,"write client error");
	
	
	//sleep(20);
	close(sockfd);		

	return 0;
}




