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

char * codeToStr(int code){
	if (code == PAPIER) return "PAPIER";
	if (code == PIERRE) return "PIERRE";
	if (code == CISEAUX) return "CISEAUX";
	return "???";
}

void endServerHandler(int sig){
	if(sig == SIGALRM){
		alarm(0);
		end_inscriptions=1;
	}
	if((sig == SIGINT) || (sig == SIGTERM)){
		printf("Joueurs inscrits : \n");
		for(int i = 0; i<MAX_PLAYERS; i++){
			printf("%s inscrit\n", tabPlayers[i].pseudo);
		}
		exit(0);
	}
}

void winner(Player p1, Player p2, char * winner){
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
int initSocketServer(int port){
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

int main(int argc, char **argv){
	int sockfd, clientsockfd;
	structMessage msg;
	int ret;
	struct sigaction endServer;
	struct pollfd fds[MAX_PLAYERS];
	char winnerName[256];

	endServer.sa_handler = endServerHandler;
	endServer.sa_flags = 0;
	ret = sigaction(SIGTERM, &endServer, NULL);
	checkNeg(ret, "sigaction error");
	ret = sigaction(SIGINT, &endServer, NULL);
	checkNeg(ret, "sigaction error");
	ret = sigaction(SIGALRM, &endServer, NULL);
	checkNeg(ret, "sigaction error");

	sockfd = initSocketServer(SERVER_PORT);
	printf("Le serveur tourne sur le port : %i \n", SERVER_PORT);
	int nbJoueurs = 0;
	int i = 0;
	alarm(TIME_INSCRIPTION);
	//on fait une boucle infinie pcq la boucle s'arretera 
	//quand le SIGALRM sera levé
	while(1){
		if(end_inscriptions == 1){
			printf("FIN DES INSCRIPTIONS\n");
			if(nbJoueurs != MAX_PLAYERS){
				printf("PARTIE ANNULEE .. PAS ASSEZ DE JOUEURS\n");
				exit(0);
			}
			//la boucle s'arretera ici
			break;
		}

		//traitement socket client
		clientsockfd = accept(sockfd, NULL, NULL);
		if(clientsockfd>0){
			//Reception du message socket client
			ret = read(clientsockfd, &msg, sizeof(msg));
			checkNeg(ret, "error reading");
			if(msg.code == INSCRIPTION_REQUEST){
				printf("Inscription demandée par le joueur : %s\n", msg.MessageText);
				strcpy(tabPlayers[i].pseudo,msg.MessageText);
				tabPlayers[i].sockfd = clientsockfd;
				i++;

				//Si il y a de la place
				if(nbJoueurs < MAX_PLAYERS){
					msg.code = INSCRIPTION_OK;
					nbJoueurs++;

				//Si il n'y a pas de place	
				}else{
					msg.code = INSCRIPTION_KO;
				}

				//Envoi du code au socket du client
				ret = write(clientsockfd, &msg, sizeof(msg));
				checkNeg(ret, "server write error");
				printf("Nb inscriptions : %d\n", nbJoueurs);
			}
		}
	}

	int nbreJoueursDejaJoue = 0;

	//boucle infinie pour le jeu
	while(1){
		for(int i = 0; i<MAX_PLAYERS; i++){
			//on prend la struct pollfd
			fds[i].fd = tabPlayers[i].sockfd;
			fds[i].events = POLLIN;
		}

		ret = poll(fds, MAX_PLAYERS, 0);
		checkNeg(ret, "server poll error");

		//verifier si joueur a joue
		for(int i = 0; i<MAX_PLAYERS; i++){
			if(fds[i].revents & POLLIN){
				//on va voir ce que le joueur a joué
				ret = read(tabPlayers[i].sockfd, &msg, sizeof(msg));
				checkNeg(ret, "server read error");

				//tester la deconnexion du client -> close (sockfd)
				if(ret!=0){
					tabPlayers[i].shot = msg.code;
					printf("%s joue %s\n", tabPlayers[i].pseudo, codeToStr(msg.code));
					nbreJoueursDejaJoue++;
				}
			}
		}

		//verifier si tous les joueurs ont joue
		if(nbreJoueursDejaJoue == MAX_PLAYERS){
			winner(tabPlayers[0], tabPlayers[1], winnerName);
			printf("GAGNANT : %s\n", winnerName);
			exit(0);
		}
	}
}