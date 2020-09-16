#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "check.h"
#include "fork.h"
#include "InscriptionRequest.h" 

pid_t fork_and_run2(void (*run)(void *,void*), void* arg0, void* arg1) {
  int childId = fork();
  checkNeg(childId, "Fork failded");

  if (childId == 0) {
    (*run)(arg0, arg1);
    exit(EXIT_SUCCESS);
  }
  return childId;
}


void run(void *argv, void *argv2){
	int *pipefd = argv;
	int *pipefd2 = argv2;

	int res = close(pipefd[1]);
	checkNeg(res, "close failed");

	int res2 = close(pipefd2[0]);
	checkNeg(res2, "close2 failed");

	//Traitement par le fils
	InscriptionRequest ir;
	int reponseFils;
	int nbre;
	while((nbre = read(pipefd[0], &ir, sizeof(ir)))>0){
		checkNeg(nbre, "Error read");
		if(ir.nbYearPastInEducation < 3){
			reponseFils = 1;
		}else{
			reponseFils = 0;
		}
		int ret = write(pipefd2[1], &reponseFils, sizeof(reponseFils));
		checkNeg(ret, "error write");
	}
	res = close(pipefd[0]);
	checkNeg(res, "close failed");

	res2 = close(pipefd2[1]);
	checkNeg(res2, "close2 failed");
}

int main(int argc, char **argv){
	int pipefd[2];
	int pipefd2[2];
	int res = pipe(pipefd);
	checkNeg(res, "pipe failed");

	int res2 = pipe(pipefd2);
	checkNeg(res2, "pipe2 failed");

	fork_and_run2(run, pipefd, pipefd2);

	res = close(pipefd[0]);
	checkNeg(res, "close failed");

	res2 = close(pipefd2[1]);
	checkNeg(res2, "close2 failed");

	InscriptionRequest ir;
	int nbre;
	int tour = 1;
	int inscriptionsAcceptees = 0;

	while((nbre = read(0, &ir, sizeof(ir)))>0){
		checkNeg(nbre, "Error read");
		//Traitement par le père
		if(tour%2==1){
			printf("Traitement par le père : <%s> <%d>\n", ir.name, ir.nbYearPastInEducation);
			if(ir.nbYearPastInEducation < 3){
				inscriptionsAcceptees++;
				printf("Valide\n");
			}else{
				printf("Invalide\n");
			}
			tour++;

		//Envoi du traitement au fils	
		}else{
			printf("Attente traitement fils : <%s> <%d>\n", ir.name, ir.nbYearPastInEducation);
			int ret = write(pipefd[1], &ir, sizeof(ir));
			checkNeg(ret, "write error");
			int reponseFils;
			int nbre2 = read(pipefd2[0], &reponseFils, sizeof(reponseFils));
			checkNeg(nbre2, "error read");
			if(reponseFils == 0){
				printf("Invalide\n");
			}else{
				inscriptionsAcceptees++;
				printf("Valide\n");
			}
			tour++;
		}
	}
	printf("Nombre de personnes validées: %d\n", inscriptionsAcceptees);

	res = close(pipefd[1]);
	checkNeg(res, "close failed");

	res2 = close(pipefd2[0]);
	checkNeg(res2, "close2 failed");
}