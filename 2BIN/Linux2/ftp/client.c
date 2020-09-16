#include "communication.h"

#define SIZE_BUF 2

int main(int argc, char *argv[])
{
	if (argc < 3) {
		printf("%s\n", "J'attends 2 arguments : IP du serveur ,Port du serveur");
		exit(0);
	}

	printf("Bienvenue dans le programme client FTP basique\n");
	printf("Vous pouvez effectuer les commandes suivantes\n");
	printf("\t 1 : lister les fichiers présents sur le serveur FTP (LS)\n");
	printf("\t 2 : récupérer le fichier index.html sur le serveur FTP (GET_INDEX)\n");
	printf("\t 3 : quitter le client FTP \n");
	
	int sockfd;
	bool arret = false;
	char buffer[SIZE_BUF];
	structMessage msg;

	sockfd = initSocketClient(argv[1], atoi(argv[2]));

	int ret = sread(0, buffer, SIZE_BUF);

	while (!arret && ret != 0) {
		switch (buffer[0]) {

			case '1': // LS
				msg.code = LS;
				arret = true;
				swrite(sockfd, &msg, sizeof(msg)); // envoie au serveur
				break;

			case '2': // GET_INDEX
				msg.code = GET_INDEX;
				arret = true;
				swrite(sockfd, &msg, sizeof(msg)); // envoie au serveur
				break;

			case '3':
				msg.code = UNKNOW_COMMAND;
				arret = true;
				swrite(sockfd, &msg, sizeof(msg)); // envoie au serveur
				break;

			default:
				printf("%s\n", "Choissisez un nombre entre 1 et 3");
				ret = sread(0, buffer, SIZE_BUF);
				break;
		}
	}

	char bufferServ[MESSAGE_SIZE];

	// attente de la réponse du serveur
	int nbChar = sread(sockfd, &bufferServ, MESSAGE_SIZE);
	while(nbChar != 0) {
		write(1, bufferServ, nbChar);
		nbChar = sread(sockfd, &bufferServ, MESSAGE_SIZE);
	}

	sclose(sockfd);

	return 0;
}