#include "communication.h"


int initSocketClient(char serverIP[16], int serverPort) {
    struct sockaddr_in addr;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    checkNeg(sockfd, "Erreur création socket client");

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(serverPort);
    inet_aton(serverIP, &addr.sin_addr);
    int ret = connect(sockfd , (struct sockaddr *) &addr, sizeof(addr));
    checkNeg(ret, "Erreur lors du connect");

    return sockfd;
}


/* return sockfd */
int initSocketServer(int port)
{
    int sockfd;
    struct sockaddr_in addr;
    //int newsockfd;

    // socket creation
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
	checkNeg(sockfd, "Error socket server");

    // setsockopt -> to avoid Address Already in Use
	int option = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int));
    
    // prepare sockaddr to bind
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    // listen on all server interfaces
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    checkNeg(bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)),"Error Bind");
    // simultaneous client max -> 5
    checkNeg(listen(sockfd, 5),"Error Listen");
	return sockfd;
}
