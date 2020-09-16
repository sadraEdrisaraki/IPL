#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include "check.h"
#include "fork.h"


/* EXERCICE 5.1 */

void sigchld_handler (int sig) {
	printf("Signal SIGPIPE reçu, je te l'annonce moray\n");
}

/* Fonction executer par le processus fils */
void run(void *argv) {
	int *pipefd = argv; // cast 

	int ret = close(pipefd[1]); // ferme l'écriture sur le pipe; le fils ne peut qu'écrire
	checkNeg(ret, "close error 1");


	ret = close(pipefd[0]); // ferme en lecture
	checkNeg(ret, "close error 2");


	//char lettre;
	//int nbChar = read(pipefd[0], &lettre, sizeof(char));
	//checkCond(nbChar != sizeof(char), "read error");

	//printf("lettre reçu par mon père: %c\n", toupper(lettre));

	//ret = close(pipefd[0]);
	//checkNeg(ret, "close error 3 ");

}


int main(int argc, char const *argv[])
{
	
	/* Armement du handler */ 
	struct sigaction newact;
	newact.sa_handler = sigchld_handler;

	int ret = sigaction(SIGPIPE, &newact, NULL); 
	checkNeg(ret, "erreur sigaction");

	/*Create pipe*/

	int pipefd[2]; // tableau des fd pour le pipe
	ret = pipe(pipefd);

	checkNeg(ret, "pipe error"); 

	fork_and_run(run, pipefd);

	ret = close(pipefd[0]); // on ferme le fd pour lire
	checkNeg(ret, "close error");

	printf("Ecrit qq chose moray:\n");
	char lettre;
	int nbRead = read(0, &lettre, 1); // lit sur le clavier
	checkCond(nbRead != sizeof(char), "read error 1");
	checkNeg(nbRead, "read error");

	int nbChar = write(pipefd[1], &lettre, sizeof(char));
	checkCond(nbChar != sizeof(char), "write error 2");

	ret = close(pipefd[1]); // le fd pour écrire
	checkNeg(ret, "close pipe error");



	return 0;
}