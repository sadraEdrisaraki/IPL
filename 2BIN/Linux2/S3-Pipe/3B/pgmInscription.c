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

/* Fonction executer par le processus fils avec les 2 tableaux*/
void run(void *argv, void *argv1) {

	int *pipefd_ecrire = argv; // on lit sur ce pipe coté fils
	int *pipefd_lire = argv1;  // on ecrit sur ce pipe coté fils

	int ret_ecrire = close(pipefd_ecrire[1]); // ferme l'écriture sur le pipe
	checkNeg(ret_ecrire, "close error");

	int ret_lecture = close(pipefd_lire[0]); // ferme la lecture sur le second pipe
	checkNeg(ret_lecture, "close error");

	// lit sur le pipe
	InscriptionRequest inscription;
	int nbChar;
	while ((nbChar = read(pipefd_ecrire[0], &inscription, sizeof(InscriptionRequest)))) {
		checkCond(nbChar != sizeof(InscriptionRequest), "read error");

		int result = 0;
		if (inscription.nbYearPastInEducation < 3) {

			result = 1;
		}
		else {
			result = 0;
		}

		int nbread = write(pipefd_lire[1], &result, sizeof(int));
		checkCond(nbread != sizeof(int), "write error");

	}

	ret_ecrire = close(pipefd_ecrire[0]);  // ferme la lecture pour dire qu'on a fini
	checkNeg(ret_ecrire, "close error");

	ret_lecture = close(pipefd_lire[1]);
	checkNeg(ret_lecture, "close error");

}


int main(int argc, char const *argv[])
{
	
	/*Create pipe*/

	int pipefd_ecrire[2]; // tableau des fd pour le pipe
	int pipefd_lire[2]; // tableau des fd pour le pipe

	int ret_ecrire = pipe(pipefd_ecrire);
	int ret_lire = pipe(pipefd_lire);

	checkNeg(ret_ecrire, "pipe error");
	checkNeg(ret_lire, "pipe error");

	/* fin de la configuration des deux pipe */


	fork_and_run(run, pipefd_ecrire, pipefd_lire); // fork

	ret_ecrire = close(pipefd_ecrire[0]); // on ferme le fd pour lire
	checkNeg(ret_ecrire, "close error");

	ret_lire = close(pipefd_lire[1]); // on ferme le fd pour écrire
	checkNeg(ret_lire, "close error");

	/* fin de la configuration du second pipe */



	InscriptionRequest inscription;

	int compteur = 0;
	int nbInscrit = 0;
	while(read(0, &inscription, sizeof(InscriptionRequest)) != 0) {

		if (compteur % 2 == 0) {
			/* demande traité par le père*/
			printf("%s %s %d\n", "Traité par le père : ", inscription.name, inscription.nbYearPastInEducation); 

			if (inscription.nbYearPastInEducation < 3) {
				nbInscrit += 1;
			}
		}

		else {

			printf("%s %s %d\n", "Traité par fils en attente : ", inscription.name, inscription.nbYearPastInEducation); 
			int nbChar = write(pipefd_ecrire[1], &inscription, sizeof(InscriptionRequest));
			checkCond(nbChar != sizeof(InscriptionRequest), "write error");

			/* lit la réponse du processus fils*/ 

			int resultat;
			int nbRead = read(pipefd_lire[0], &resultat, sizeof(int));
			checkCond(nbRead != sizeof(int), "read error");
			nbInscrit += resultat; 

		} 
		
		compteur++;

	}

	printf("Nombre d'inscrit : %d  \n",  nbInscrit);


	ret_ecrire = close(pipefd_ecrire[1]); // le fd pour écrire
	checkNeg(ret_ecrire, "close pipe error");

	ret_lire = close(pipefd_lire[0]); // le fd pour écrire
	checkNeg(ret_lire, "close pipe error");


	return 0;
}