#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "check.h"
#include "utils.h"

#define SERVER_PORT		9090
#define BUFFER_SIZE		1024

/**
 * Basic sample that show the different steps to have a listening server
 * In this sample, syscall are not checked to concentrate on the different steps but you must check the syscall for the exercices !
 */

/* Initialise le socket d'écoute et return son sockfd */
int initSocketServer(char ServerIP[16], int port)
{	
	struct sockaddr_in addr;

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	checkNeg(sockfd, "Impossible de créer le socket");

	// Remplis la structure pour se connecter au serveur.
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ServerIP);


	int ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
	checkNeg(ret, "Erreur dans le connect !");

	return sockfd;
}

int main(int argc, char *arg[])
{
    int sockfd; // file descriptor du socket
    char ip[18];
    char ligne[BUFFER_SIZE];
    char pageName [BUFFER_SIZE];
    char request[BUFFER_SIZE];
    char response[BUFFER_SIZE];
    int ret;
    int fdHtmlPage;
    int nbChar;

    // ouvre le fichier 
    int fdSiteMap = open("sitemap.txt", O_RDONLY);
    checkNeg(fdSiteMap, "Impossible d'ouvrir le fichier");

    hostname_to_ip("ochoquet.be", ip);
    printf("IPv4 ochoquet.be : %s\n", ip);

    // lit le fichier 'sitemap.txt'
    while(readline(fdSiteMap, ligne)) {

    	printf("Ligne :%s, strlen: %lu \n", ligne, strlen(ligne));

    	sprintf(pageName,"%s",strrchr(ligne,'/')+1);
    	printf("Page Name %s\n", pageName );
    	// Connexion à chaque nouvelle page lu
    	sockfd = initSocketServer(ip, SERVER_PORT);
    	printf("Le serveur tourne sur le port : %i \n",SERVER_PORT);

    	sprintf(request, "GET %s HTTP/1.0\r\nHost: %s\r\n\r\n", ligne, "ochoquet.be");

    	// écris dans le socket la requete http.
    	ret =  write(sockfd, request, strlen(request));
    	checkNeg(ret, "Erreur dans le write");

    	//Créer les page web avant de stocker à l'intérieur le contenu html.
    	fdHtmlPage = open(pageName, O_RDWR | O_TRUNC | O_CREAT, 0644); // si elle n'existe pas, elle son créée.
    	checkNeg(fdHtmlPage, "Erreur ouverture page html");

    	// lit la réponse de la requête précédente. Et écrit dans le fichier.
    	while((nbChar = read(sockfd, response, BUFFER_SIZE))) {
    		checkNeg(nbChar, "Erreur dans la lecture de la réponse");
    		write(fdHtmlPage, response, nbChar);
    	}
    	ret = close(sockfd);
    	checkNeg(ret, "Erreur fermeture socket de lecture");
    	ret = close(fdHtmlPage);
    	checkNeg(ret, "Erreur fermeture fichier");
    }
    return 0;
}