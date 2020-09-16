#include "messages.h"


int initSocketClient(char ServerIP[16], int Serverport)
{

	// TODO

}


int main(int argc, char** argv)
{

	char pseudo[MAX_PSEUDO];
	int sockfd;
	int ret;
	structMessage msg;
			
		
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
	}
		
	close(sockfd);		

	return 0;
}




