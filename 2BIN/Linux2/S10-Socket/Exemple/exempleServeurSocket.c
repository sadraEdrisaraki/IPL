#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Basic sample that show the different steps to have a listening server
 * In this sample, syscall are not checked to concentrate on the different steps but you must check the syscall for the exercices !
 */

int main(int argc, char *arg[])
{
    int sockfd; // file descriptor du socket
    struct sockaddr_in addr;
    int newsockfd;
    int val;

    // 1 : socket creation
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // toujours 0 pour le protocole : obselete

    // setsockopt -> to avoid Address Already in Use : permet de réutiliser le port
	int option = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int));
    
    // 2: prepare sockaddr to bind
    memset(&addr, 0, sizeof(addr)); // initialise des 0 partout par prudence 
    addr.sin_family = AF_INET;
    // listen port 9090 !!!
    addr.sin_port = htons(9090);
    // listen on all server interfaces
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // Ecoute sur toutes ses interfaces(cartes réseaux)

    bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    // simultaneous client max -> 5 (backlog)
    listen(sockfd, 5);
    printf("Le serveur tourne sur le port 9090\n");
    // accept client connection
    newsockfd = accept(sockfd, NULL, NULL); // appel système bloquant
    // read message from client
    read(newsockfd, &val, sizeof(int)); // un entier est envoyé au serveur
    printf("Valeur reçue : %i\n", val);
    // close connection client
    close(newsockfd);
    // close listen socket
    close(sockfd);
    return 0;

}
