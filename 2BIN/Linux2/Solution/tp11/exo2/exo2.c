#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <poll.h>
#include "check.h"

#define BUFFERSIZE 50
#define TIMEMILLISEC 10000
#define NB_CHILD 3

static pid_t fork_and_run(void (*handler)(int *), int *pipe){
	pid_t pid = fork();
	checkNeg(pid, "Fork failed\n");
	if (pid == 0){
		(*handler)(pipe);
		exit(EXIT_SUCCESS);
	}else{
		return pid;
	}
}

void childHandler(int* argv){
	int* pipefd = argv;
	int ret;
	char buffer[BUFFERSIZE];

	ret = close(pipefd[0]);
	checkNeg(ret, "close pipe[0] child");
	int random = 1;
	//Envoi des inscriptions
	for(int i = 0; i<10; i++){
		//Solution temp pour random pcq usleep ne marche pas
		//int random = rand() % TIMEMILLISEC;
		//dort
		sleep(1);

		sprintf(buffer, "Fils %i : inscription %d\n", getpid(), random);
		//on envoie l'inscription via le pipe
		ret = write(pipefd[1], buffer, strlen(buffer));
		checkNeg(ret, "write child pipe");
		random++;
	}
	ret = close(pipefd[1]);
	checkNeg(ret, "close child pipe[1]");
}

int main(int argc, char **argv){
	int pidChild[NB_CHILD];
	int pipeChild[NB_CHILD][2];
	int ret;
	char buffer[BUFFERSIZE];
	int nbChar;
	struct pollfd fds[NB_CHILD];

	for(int i = 0; i<NB_CHILD; i++){
		//creation du pipe pour chaque enfant
		ret = pipe(pipeChild[i]);
		checkNeg(ret, "pipe inscr");

		pidChild[i] = fork_and_run(childHandler, pipeChild[i]);
		checkNeg(pidChild[i], "fork inscr");

		//creation du poll pour chaque enfant
		fds[i].fd = pipeChild[i][0];
		fds[i].events = POLLIN;
	}

	while(1){
		ret = poll(fds, NB_CHILD, 0);
		checkNeg(ret, "erreur poll");

		for(int i = 0; i < NB_CHILD; i++){
			if(fds[i].revents & POLLIN){
				nbChar = read(pipeChild[i][0], buffer, BUFFERSIZE);
				checkNeg(nbChar, "read parent pipeInscr1");

				nbChar = write(1, buffer, nbChar);
				checkNeg(nbChar, "write parent stdout");
			}
		}
	}
}