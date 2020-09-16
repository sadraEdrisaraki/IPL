#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "check.h"
#include "fork.h"


typedef struct {
	char name[256];
	char firstname[256];
	int nbYearPastInEducation;	
} InscriptionRequest;

/* Fonction executer par le processus fils */
void run(void *argv) {
	int *pipefd = argv; // cast 

	int ret = close(pipefd[1]); // ferme l'écriture sur le pipe
	checkNeg(ret, "close error");

	ret = close(pipefd[0]);
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

	/* fin de la configuration du pipe */

	InscriptionRequest inscription;


	printf("%s\n", "ici");
	while(read(0, &inscription, sizeof(InscriptionRequest)) != 0) {
		printf("%s\n", "boucle" );
		// TO do

	}



	ret = close(pipefd[1]); // le fd pour écrire
	checkNeg(ret, "close pipe error");


	return 0;
}