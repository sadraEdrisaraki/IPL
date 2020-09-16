#include <signal.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include <poll.h>
#include <stdbool.h>
/* Used by server and client */
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
/* struct sockaddr_in */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "check.h"
#include "fork.h"

#define MESSAGE_SIZE 8192

static bool stop = false;

/* return sockfd */
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

	/* no bind error */
	ret = listen(sockfd, 10);
	/* no listen error */
	return sockfd;
}

static const char *random_monster()
{
	int random_number = rand() % 7 + 1;
	switch (random_number)
	{
	case 1:
		return "skeleton";
		break;
	case 2:
		return "stegosaurus";
		break;
	case 3:
		return "milk";
		break;
	case 4:
		return "bunny";
		break;
	case 5:
		return "duck";
		break;
	case 6:
		return "cock";
		break;
	case 7:
		return "dragon";
		break;
	}
	return "random number server ????";
}

static void exec_cowsay(char *namefile, char *msg)
{

	int fd = open(namefile, O_WRONLY | O_TRUNC | O_CREAT, 0700);
	checkNeg(fd, "open failed");
	dup2(fd, 1);
	execl("/usr/games/cowsay", "cowsay", "-f", random_monster(), msg, NULL);
	perror("Exec failed\n");
	exit(EXIT_FAILURE);
}

static void exec_rm_files()
{
	execl("/bin/bash", "bash", "-c", "rm -rf resultTest*", NULL);
	perror("Exec failed\n");
	exit(EXIT_FAILURE);
}

void endServerHandler(int sig)
{
	if ((sig == SIGINT) || (sig == SIGTERM))
	{
		stop = true;
	}
}

int main(int argc, char **argv)
{
	int sockfd, newsockfd, filefd;
	struct sigaction endServer;
	int ret, nbChar;
	char buffer[MESSAGE_SIZE];
	int childpid;
	char namefile[1024];
	struct sockaddr_in addr;
	socklen_t addr_size;
	int random_number;
	char msg[MESSAGE_SIZE];

	srand(time(NULL));

	if (argc != 2)
	{
		printf("%s\n", "Usage argv[0] ServerPort");
		exit(1);
	}

	endServer.sa_handler = endServerHandler;
	endServer.sa_flags = 0;
	ret = sigaction(SIGTERM, &endServer, NULL);
	checkNeg(ret, "sigaction error");
	ret = sigaction(SIGINT, &endServer, NULL);
	checkNeg(ret, "sigaction error");

	addr_size = sizeof(struct sockaddr_in);
	sockfd = initSocketServer(atoi(argv[1]));
	printf("Le serveur est à l'écoute sur le port : %i \n", atoi(argv[1]));


	while (1)
	{
		//ret = poll(fds, nbSockfd, 0);
		checkNeg(ret, "server poll error");

		// trt accept

		newsockfd = accept(sockfd, (struct sockaddr *)&addr, &addr_size);
		checkNeg(newsockfd, "erreur accept");

		ret = read(newsockfd, msg, sizeof(msg));
		checkNeg(ret, "server read error");

		printf("MESSAGE RECU DE : %s - ADRESSE IP CLIENT : %s\n", msg, inet_ntoa(addr.sin_addr));

		if ((msg != NULL) && (strlen(msg) > 0))
		{

			time_t current_time;
			current_time = time(NULL);
			random_number = rand();
			sprintf(namefile, "%s_%i_%ld", "resultTest", random_number, current_time);
			childpid = fork_and_run(exec_cowsay, namefile, msg);
			waitpid(childpid, NULL, 0);
			memset(&buffer, 0, sizeof(buffer));
			filefd = open(namefile, O_RDONLY);
			checkNeg(filefd, "server open file error");
			nbChar = read(filefd, buffer, MESSAGE_SIZE);
			checkNeg(nbChar, "server read file error");
			printf("REPONSE ENVOYEE PAR LE SERVEUR (doit être identique chez le client): \n");
			printf("%s\n", buffer);
			ret = write(newsockfd, buffer, sizeof(msg));
			checkNeg(ret, "server write error");
		}
		else
		{
			sprintf(buffer, "message vide\n");
			ret = write(newsockfd, buffer, sizeof(msg));
			checkNeg(ret, "server write error");
		}
		sleep(2);
		close(newsockfd);
	}

	if (stop == 1)
	{
		printf("FIN SERVEUR : destruction fichiers resultTest\n");
		fork_and_run_simple(exec_rm_files);
		exit(0);
	}
}
