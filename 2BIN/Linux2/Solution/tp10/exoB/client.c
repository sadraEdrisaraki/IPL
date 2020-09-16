#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "check.h"
#include "utils.h"

#define BUFFER_SIZE 1024


int initSocketClient(char ServerIP[16], int Serverport){
	
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	checkNeg(sockfd, "error socket client");

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(Serverport);

	//Cst quoi la difference entre inet_addr et inet_aton ?
	addr.sin_addr.s_addr = inet_addr(ServerIP);
	//inet_aton(ServerIP, &addr.sin_addr);
	int ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));

	checkNeg(ret, "connect client error");
	return sockfd;
}

int main(int argc, char **argv){
	int sockfd;
	int ret, nbChar;
	char ligne[BUFFER_SIZE];
	char request[BUFFER_SIZE];
	char ip[18];
	char response[BUFFER_SIZE];
	char pageName[BUFFER_SIZE];
	int fdHTMLPage;

	//Ouvrir le fichier
	int fdSiteMap = open("sitemap.txt", O_RDONLY);
	checkNeg(fdSiteMap, "open sitemap error");

	hostname_to_ip("ochoquet.be",ip);
	printf("IPv4 ochoquet.be : %s\n", ip);

	while(readline(fdSiteMap, ligne)){
		//Afficher Ligne : ..
		printf("Ligne : %s, strlen: %ld\n", ligne, strlen(ligne));
		
		//Afficher Page Name : ..
		sprintf(pageName,"%s",strrchr(ligne,'/')+1);
		printf("Page Name : %s\n", pageName);

		sockfd = initSocketClient(ip, 80);
		checkNeg(sockfd, "socket init client error");

		//Requête envoyée via un socket de connexion
		sprintf(request, "GET %s HTTP/1.0\r\nHost: %s\r\n\r\n", ligne, "ochoquet.be");
		ret = write(sockfd, request, strlen(request));
		checkNeg(ret, "error writing request");

		//Ex : ouvrir un fichier index.html
		fdHTMLPage = open(pageName, O_RDWR | O_TRUNC | O_CREAT, 0644);
		checkNeg(fdHTMLPage, "error open fdHTMLPage");

		//On va lire ce qu'il y a dans le socket
		//Ex : dans le socket il y a la requete du site .../index.html
		while((nbChar = read(sockfd,response, BUFFER_SIZE))){
			checkNeg(nbChar, "error read response");

			//Ecrire dans le fichier 
			write(fdHTMLPage, response, nbChar);
		}

		ret = close(sockfd);
		checkNeg(ret, "error close sockfd");
		ret = close(fdHTMLPage);
		checkNeg(ret, "error close fdHTMLPage");
	}

	res = close(fdSiteMap);
	checkNeg(res, "error close fdSiteMap");
}