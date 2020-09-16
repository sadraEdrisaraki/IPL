#include "messages.h"
#include <signal.h>
#include <poll.h>

#define MAX_PLAYERS 	2
#define TIME_INSCRIPTION 	10

typedef struct Player
{
	char pseudo[MAX_PSEUDO];
	int sockfd;
	int shot; // piere, papier ou ciseaux
} Player;

/* Variable Globale */
int fin_inscription = 0; // si vaut 1, l'inscription est fini
Player tabPlayers[MAX_PLAYERS]; // tableau des joueurs


/* Reçoit un code en paramètre et vérifie si ça appartient à un code (PAPIER, PIERRE,..). Grâce aux #define, les PAPIERS vont etre transformer par leur 
valeur correspondante. */
char * codeToStr(int code) {
	if (code == PAPIER) return "PAPIER";
	if (code == PIERRE) return "PIERRE";
	if (code == CISEAUX) return "CISEAUX";
	return "???";
}

/* Prend 2 joueurs en paramètre ainsi qu'une chaine de caractère qui ba contenir le nom du gagnant. */
void winner(Player p1, Player p2, char * winnerName) {
	if ((p1.shot == PAPIER) && (p2.shot == PAPIER)) strcpy(winnerName, "EGALITE");
	if ((p1.shot == PAPIER) && (p2.shot == PIERRE)) strcpy(winnerName, p1.pseudo);
	if ((p1.shot == PAPIER) && (p2.shot == CISEAUX)) strcpy(winnerName, p2.pseudo);

	if ((p1.shot == PIERRE) && (p2.shot == PAPIER)) strcpy(winnerName, p2.pseudo);
	if ((p1.shot == PIERRE) && (p2.shot == PIERRE)) strcpy(winnerName, "EGALITE");
	if ((p1.shot == PIERRE) && (p2.shot == CISEAUX)) strcpy(winnerName, p1.pseudo);

	if ((p1.shot == CISEAUX) && (p2.shot == PAPIER)) strcpy(winnerName, p1.pseudo);
	if ((p1.shot == CISEAUX) && (p2.shot == PIERRE)) strcpy(winnerName, p2.pseudo);
	if ((p1.shot == CISEAUX) && (p2.shot == CISEAUX)) strcpy(winnerName, "EGALITE");


}

/* Gestionnaire de signaux */
void serverHandler(int sig) {
	if (sig == SIGALRM){
		alarm(0);
		fin_inscription = 1;
	}
}

/* Initialise le socket du serveur */
int initSocketServer(int port)
{
	int sockfd;
	struct sockaddr_in addr;
	int ret;

	/* AF_INET -> internet comunication , AF_UNIX -> local communication */
	// SOCK_STREAM -> TCP
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	checkNeg(sockfd, "socket server creation error");

	// setsockopt -> to avoid Address Already in Use
	int option = 1;
	ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int));
	checkNeg(ret, "socket server setsockopt error");

	/* no socket error */
	memset(&addr, 0, sizeof(addr)); /* en System V */
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	checkNeg(ret, "server bind error");
	ret = listen(sockfd, 10); // max 10 clients
	checkNeg(ret, "server listen error");

	return sockfd;
}

int main(int argc, char const *argv[])
{
	int sockfd, newsockfd;
	struct pollfd fds[1024];
	int nbSockfd = 0;
	int nbPlayers = 0;
	int ret;
	structMessage msg;
	struct sigaction serverSignaux;
	char winnerName[256];

	serverSignaux.sa_handler = serverHandler;
	serverSignaux.sa_flags = 0;
	ret = sigaction(SIGALRM, &serverSignaux, NULL);
	checkNeg(ret, "sigaction error");

	sockfd = initSocketServer(SERVER_PORT);
	printf("Le serveur tourne sur le port %i \n", SERVER_PORT);

	/* initialise le tableau */ 
	fds[nbSockfd].fd = sockfd;
	fds[nbSockfd].events = POLLIN;
	nbSockfd++;

	// On ne gere pas le poll ici car la connexion et l'envoie de message et fait en un coup
	// On demande au client d'écrire son nom avant d'établir la connexion.

	/* boucle inscription */
	alarm(TIME_INSCRIPTION); // enclenche l'alarm
	while(1) {

		// Après le timeout pour arreter la boucle
		if(fin_inscription) {
			printf("%s\n", "FIN DES INSCRIPTIONS");
			if (nbPlayers != MAX_PLAYERS) {
				printf("PARTIE ANNULEE ... PAS ASSEZ DE JOUEURS\n");
				exit(0); // termine le programme
			}
			break;
		}

		/* client trt */ // accepte une nouvelle connexion si il y en a 
		newsockfd = accept(sockfd, NULL,NULL);
		if (newsockfd > 0 ) /* no error */
		{
			ret = read(newsockfd, &msg, sizeof(msg)); //lit les données sur le socket du client
			checkNeg(ret,"server read error");

			if (msg.code == INSCRIPTION_REQUEST){
					printf("Inscription demandée par le joueur : %s\n", msg.MessageText);

					if (nbPlayers < MAX_PLAYERS)
					{
						// copie le nom du joueur dans le tableau avec tous les noms des autres joueurs
						strcpy(tabPlayers[nbPlayers].pseudo, msg.MessageText);
						tabPlayers[nbPlayers].sockfd = newsockfd;	
						msg.code = INSCRIPTION_OK;
						nbPlayers++;						
					}
					else
					{
						msg.code = INSCRIPTION_KO;
					}
					ret = write(newsockfd, &msg, sizeof(msg));
					checkNeg(ret,"server write error");
					printf("Nb Inscriptions : %i\n", nbPlayers);
			}	
		}		
	}

	/* Init le poll*/
	for (int i = 0; i < MAX_PLAYERS; ++i)
	{
		fds[i].fd = tabPlayers[i].sockfd; // surveiller les socket des clients
		fds[i].events = POLLIN;
	}
	int nbPlayersAlreayPlayed = 0;

	/* Boucle du jeu */
	while(1) {

		ret = poll(fds, MAX_PLAYERS, -1);
		checkNeg(ret, "server poll error");

		for (int i = 0; i < MAX_PLAYERS; ++i)
		{
			// il y a quelque chose à lire pour le player i
			if (fds[i].revents & POLLIN) { //revents veut dire evenements de retour
				ret = read(fds[i].fd, &msg, sizeof(msg));
				checkNeg(ret, "server read error");

				// si c'est = à 0, ça veut dire qu'on a rien lu.
				if (ret != 0) {
					tabPlayers[i].shot = msg.code;
					printf("%d\n", tabPlayers[i].shot);
					printf("%s joue %s \n", tabPlayers[i].pseudo, codeToStr(msg.code));
					nbPlayersAlreayPlayed++;
				} else if (ret == 0) {
					//printf("%s\n", "Le client s'est déco");
					// on pourrait close le socket du client ici.
				}
			}
		}

		if (nbPlayersAlreayPlayed == MAX_PLAYERS) {
			winner(tabPlayers[0], tabPlayers[1], winnerName);
			printf("GAGNANT : %s\n", winnerName);
			exit(0);
		}
	}

	// ferme les connexion des clients
	for (int i = 0; i < MAX_PLAYERS; ++i)
	{
		close(tabPlayers[i].sockfd);
	}
	// ferme le socket principale
	close(sockfd);
}



