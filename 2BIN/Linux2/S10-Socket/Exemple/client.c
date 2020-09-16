#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Basic sample that show the different steps to have a client connected to a server
 * In this sample, syscall are not checked to concentrate on the different steps but you must check the syscall for the exercices !
 */

int main(int argc, char *arg[])
{

    int sockfd;
    struct sockaddr_in addr;
    int val;

    // 1 : socket creation
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // prepare socket to connect
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    // connect to server port
    addr.sin_port = htons(9090); // le port sur serveur
    // connect to server address -> localhost
    inet_aton("127.0.0.1",&addr.sin_addr);
    // 2 : Connect to server
    connect(sockfd, (struct sockaddr *) &addr, 	sizeof(addr));
    val = 7;
    printf("Client envoie la valeur 7 au serveur\n");
    write(sockfd,&val,sizeof(int));
    close(sockfd);
}