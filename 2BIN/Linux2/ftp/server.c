#include "communication.h"

void transfer_file(char* pathfile, int sockfd) {

	char buffer[MESSAGE_SIZE]; 

	int fd = sopen(pathfile, O_RDONLY, 0);

	int nbChar = sread(fd, buffer, MESSAGE_SIZE);

	while( nbChar != 0) {
		swrite(sockfd, &buffer, nbChar);
		nbChar = sread(fd, buffer, MESSAGE_SIZE);
	}

	sclose(fd);
}

void executerLs(char *argv){
	execl("/bin/ls", "/bin/ls", "-l", argv , NULL);
}

void traitementLs(int sockfd) {
	int fd_stdout; // sortie standard
	int ret;
	int fd = sopen("ls.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);

	fd_stdout = dup(1);

	checkNeg(fd_stdout, "dup erreur ");

	ret = dup2(fd, 1);
	checkNeg(ret, "dup2 erreur");

	int child = fork_and_run(executerLs, "./ftpdir");

	swaitpid(child, NULL, 0);

	ret = dup2(fd_stdout, 1); // rétablir la sortie standard
	checkNeg(ret, "dup2 erreur");

	transfer_file("ls.txt", sockfd);

	sclose(fd);
}

int main(int argc, char *argv[])
{

	if (argc < 2 ) {
		printf("%s\n", "J'attends 1 argument : Port du serveur");
		exit(0);
	}

	int sockfd;
	int newSockFd;
	structMessage msg;

	int serveur_port = atoi(argv[1]);

	sockfd = initSocketServer(serveur_port);
	printf("Le serveur tourne sur le port : %i \n", serveur_port);

	while(1) {

		newSockFd = accept(sockfd, NULL, NULL);

		if (newSockFd > 0) { // pas d'erreur

			sread(newSockFd, &msg, sizeof(msg));

			if (msg.code == LS) {
				printf("100\n");
				traitementLs(newSockFd);
			} else if (msg.code == GET_INDEX) {
				printf("200\n");
				transfer_file("./ftpdir/index.html", newSockFd);
			}
		}
		sclose(newSockFd); // ferme socket client après la requete
	}

	sclose(sockfd);

	return 0;
}