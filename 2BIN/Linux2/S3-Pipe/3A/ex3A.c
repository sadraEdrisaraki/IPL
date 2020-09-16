#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "check.h"
#include "fork.h"

/* Fonction executer par le processus fils */
void run(void *argv) {
	int *pipefd = argv; // cast 

	int ret = close(pipefd[1]); // ferme l'écriture sur le pipe
	checkNeg(ret, "close error");

	char lettre;
	int nbChar = read(pipefd[0], &lettre, sizeof(char));
	checkCond(nbChar != sizeof(char), "read error");

	printf("lettre reçu par mon père: %c\n", toupper(lettre));

	ret= close(pipefd[0]);
	checkNeg(ret, "close error");

}


int main(int argc, char const *argv[])
{
	
	/*Create pipe*/

	int pipefd[2]; // tableau des fd pour le pipe
	int ret = pipe(pipefd);

	checkNeg(ret, "pipe error");

	fork_and_run(run, pipefd);

	ret = close(pipefd[0]); // on ferme le fd pour lire
	checkNeg(ret, "close error");

	char lettre;
	int nbRead = read(0, &lettre, 1); // lit sur le clavier
	checkNeg(nbRead, "read error");

	int nbChar = write(pipefd[1], &lettre, sizeof(char));
	checkCond(nbChar != sizeof(char), "write error");

	ret = close(pipefd[1]); // le fd pour écrire
	checkNeg(ret, "close pipe error");



	return 0;
}