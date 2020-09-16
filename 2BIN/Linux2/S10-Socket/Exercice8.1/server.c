#include "messages.h"
#include <signal.h>

#define MAX_PLAYERS	2

// Represente un joueur
typedef struct Player {
	char pseudo[MAX_PSEUDO];
	int sockfd;
}Player;


/* global variables */
Player tabPlayers[MAX_PLAYERS]; // Tableau de Player
int nbPlayers;

// Gestionnaire de signaux
void endServerHandler(int sig)
{
	int i;
	printf("\nJoueurs inscrits : \n");
	for (i=0;i<nbPlayers;i++)
	{
		printf("  - %s inscrit\n",tabPlayers[i].pseudo);
	}
	exit(0);
}


/* Initialise le socket d'écoute et return son sockfd */
int initSocketServer(int port)
{	
	struct sockaddr_in addr;

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	checkNeg(sockfd, "Impossible de créer le socket");

	int option =1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int));

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));

	listen(sockfd, MAX_PLAYERS);

	return sockfd;
}


int main (int argc, char ** argv)
{
	int sockfd, newsockfd;
	structMessage msg;
	int ret;
	struct sigaction endServer;

	endServer.sa_handler = endServerHandler;
	ret = sigaction(SIGTERM,&endServer,NULL);
	checkNeg(ret,"sigaction error");
	ret = sigaction(SIGINT,&endServer,NULL);
	checkNeg(ret,"sigaction error");
	

	sockfd = initSocketServer(SERVER_PORT);	
	printf("Le serveur tourne sur le port : %i \n",SERVER_PORT);
	nbPlayers = 0;

	// boucle principale du seveur
	while (1)	
	{
		
		/* client trt */ // accepte une nouvelle connexion si il y en a 
		newsockfd = accept(sockfd, NULL,NULL);
		printf("accept\n");
		if (newsockfd > 0 ) /* no error : un ChecNeg est suffisant aussi*/
		{
			
			ret = read(newsockfd,&msg,sizeof(msg));
			checkNeg(ret,"server read error");

			if (msg.code == INSCRIPTION_REQUEST){
					printf("Inscription demandée par le joueur : %s\n", msg.MessageText);

					if (nbPlayers < MAX_PLAYERS)
					{
						// copie le nom du joueur dans le tableau avec tous les noms des joueurs
						strcpy(tabPlayers[nbPlayers].pseudo, msg.MessageText);
						tabPlayers[nbPlayers].sockfd = newsockfd;	
						msg.code = INSCRIPTION_OK;
						nbPlayers++;						
					}
					else
					{
						msg.code = INSCRIPTION_KO;
					}
					ret = write(newsockfd, &msg,sizeof(msg));
					checkNeg(ret,"server write error");
					printf("Nb Inscriptions : %i\n", nbPlayers);
			}	
				
		}		
	}

}
