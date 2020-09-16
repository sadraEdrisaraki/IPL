#include "messages.h"
#include <signal.h>
#include <poll.h>

#define MAX_PLAYERS		2
#define TIME_INSCRIPTION	10

typedef struct Player {
	char pseudo[MAX_PSEUDO];
	int sockfd;
	int shot;
}Player;


/* globals variables */
Player tabPlayers[MAX_PLAYERS];
int end_inscriptions = 0;

char * codeToStr(int code)
{
	if (code == PAPIER) return "PAPIER";
	if (code == PIERRE) return "PIERRE";
	if (code == CISEAUX) return "CISEAUX";
	return "???";
}

void endServerHandler(int sig)
{
	if ((sig == SIGINT) || (sig == SIGTERM))
	{	

		int i;
		printf("Joueurs inscrits : \n");
		for (i=0;i<MAX_PLAYERS;i++)
		{
			printf("%s inscrit\n",tabPlayers[i].pseudo);
		}
		exit(0);
	}
	if (sig == SIGALRM)
	{
		alarm(0);
		end_inscriptions=1;
	}
}

void winner(Player p1, Player p2, char * winner)
{	
	if ((p1.shot == PAPIER) && (p2.shot == PAPIER)) strcpy(winner,"EGALITE");
	if ((p1.shot == PAPIER) && (p2.shot == CISEAUX)) strcpy(winner, p2.pseudo);
	if ((p1.shot == PAPIER) && (p2.shot == PIERRE)) strcpy(winner, p1.pseudo);

	if ((p1.shot == PIERRE) && (p2.shot == PAPIER)) strcpy(winner, p2.pseudo);
	if ((p1.shot == PIERRE) && (p2.shot == CISEAUX)) strcpy(winner, p1.pseudo);
	if ((p1.shot == PIERRE) && (p2.shot == PIERRE)) strcpy(winner,"EGALITE");

	if ((p1.shot == CISEAUX) && (p2.shot == PAPIER)) strcpy(winner, p1.pseudo);
	if ((p1.shot == CISEAUX) && (p2.shot == CISEAUX)) strcpy(winner,"EGALITE"); 
	if ((p1.shot == CISEAUX) && (p2.shot == PIERRE)) strcpy(winner, p2.pseudo);
	return ;
}


/* return sockfd */
int initSocketServer(int port)
{
	int sockfd;
	struct sockaddr_in addr;	
	int ret;

	/* AF_INET -> internet comunication , AF_UNIX -> local communication */	
	// SOCK_STREAM -> TCP
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	checkNeg(sockfd,"socket server creation error");
	// setsockopt -> to avoid Address Already in Use
	int option = 1;
	ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int));
	checkNeg(ret,"socket server setsockopt error");
	
	/* no socket error */
	memset(&addr,0,sizeof(addr)); /* en System V */
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ret = bind(sockfd,(struct sockaddr *)&addr,sizeof(addr));
	checkNeg(ret,"server bind error");

	/* no bind error */
	ret = listen(sockfd,5);
	/* no listen error */
	return sockfd;
}


int main (int argc, char ** argv)
{
	int sockfd, newsockfd, i;
	structMessage msg;
	int ret;
	struct sigaction endServer;
	//fd_set rfds;
	struct pollfd fds[MAX_PLAYERS];
	char winnerName[256];

	endServer.sa_handler = endServerHandler;
	endServer.sa_flags = 0;
	ret = sigaction(SIGTERM,&endServer,NULL);
	checkNeg(ret,"sigaction error");
	ret = sigaction(SIGINT,&endServer,NULL);
	checkNeg(ret,"sigaction error");
	ret = sigaction(SIGALRM,&endServer,NULL);
	checkNeg(ret,"sigaction error");
	

	sockfd = initSocketServer(SERVER_PORT);	
	printf("Le serveur tourne sur le port : %i \n",SERVER_PORT);
	i=0;
	int nbPLayers = 0;

	// loop inscriptions
	alarm(TIME_INSCRIPTION);
	while (1)	
	{
		if (end_inscriptions) 
		{
			printf("FIN DES INSCRIPTIONS\n");
			if (nbPLayers != MAX_PLAYERS)
			{
				printf("PARTIE ANNULEE .. PAS ASSEZ DE JOUEURS\n");
				exit(0);
			} 
			break;
		}		

		/* client trt */
		newsockfd = accept(sockfd, NULL,NULL);
		if (newsockfd > 0 ) /* no error */
		{
			
			ret = read(newsockfd,&msg,sizeof(msg));
			checkNeg(ret,"server read error");

			if (msg.code == INSCRIPTION_REQUEST){
					printf("Inscription demandée par le joueur : %s\n", msg.MessageText);

					strcpy(tabPlayers[i].pseudo,msg.MessageText);
					tabPlayers[i].sockfd = newsockfd;	
					i++;

					if (nbPLayers < MAX_PLAYERS)
					{
						msg.code = INSCRIPTION_OK;
						nbPLayers++;
						
					}
					else
					{
						msg.code = INSCRIPTION_KO;
					}
					ret = write(newsockfd, &msg,sizeof(msg));
					checkNeg(ret,"server write error");
					printf("Nb Inscriptions : %i\n", nbPLayers);
			}	
				
		}
				
	}

	int nbPlayersAlreadyPlayed = 0;
	

	// loop game
	while (1) {
		// init select 
		//FD_ZERO(&rfds);
		for (i=0;i<MAX_PLAYERS;i++)
		{
			//printf("sockfd %i\n",tabPlayers[i].sockfd);
			//FD_SET(tabPlayers[i].sockfd,&rfds);
			fds[i].fd = tabPlayers[i].sockfd;
			fds[i].events = POLLIN;
		}
		//ret = select(FD_SETSIZE,&rfds,NULL,NULL,NULL);
		//checkNeg(ret,"server select error");

		ret = poll(fds,MAX_PLAYERS,0);
		checkNeg(ret,"server poll error");

		// check player something to read
		for (i=0;i<MAX_PLAYERS;i++)
		{			
			//if (FD_ISSET(tabPlayers[i].sockfd,&rfds))
			if (fds[i].revents & POLLIN)
			{
							
				ret = read(tabPlayers[i].sockfd,&msg,sizeof(msg));
				checkNeg(ret,"server read error");
				// FD_ISSET sera positionné si le client fait un close(sockfd)
				// tester la déconnexion du client -> close (sockfd)
				if (ret != 0)
				{ 
				

					tabPlayers[i].shot = msg.code;
					printf("%s joue %s\n",tabPlayers[i].pseudo, codeToStr(msg.code));
					nbPlayersAlreadyPlayed++;
					
				}
				// ne pas utiliser FD_CLR -> ne fonctionne pas
				//FD_CLR(tabPlayers[i].sockfd,&rfds);

			}
		}
		
		//check end tour
		if (nbPlayersAlreadyPlayed == MAX_PLAYERS)
		{
			winner(tabPlayers[0], tabPlayers[1], winnerName);
			printf("GAGNANT : %s",winnerName);
			exit(0);
		}
	}
		

}
