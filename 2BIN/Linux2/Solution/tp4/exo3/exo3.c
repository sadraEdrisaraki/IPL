#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "check.h"
#include "fork.h"

int compt = 7;

void sighandler(int signum){
	if(signum==SIGCHLD){
		wait(NULL);
		printf("Fin du père\n");
		exit(EXIT_SUCCESS);
	}else{
		printf("--> Signal SIGUSR1 reçu! ");
		compt--;
	}
}

void childHandler(void *argv){
	//armement du handler de signal SIGUSR1
	struct sigaction newact;
	newact.sa_handler = sighandler;
	int ret = sigemptyset(&newact.sa_mask);
	checkNeg(ret, "erreur sigemptyset");
	newact.sa_flags = 0;

	ret = sigaction(SIGUSR1, &newact, NULL);
	checkNeg(ret, "error sigaction");

	printf("OK il me reste %d vies\n", compt);
	int valeurPrecedente = compt;
	while(compt != 0){
		if(compt != valeurPrecedente){
			printf("OK il me reste %d vies\n", compt);
			valeurPrecedente = compt;
		}
	}
	printf("That's all, folks!\nFin du fils\n");
	exit(EXIT_SUCCESS);
}

int main(int argc, char **argv){
	int ret;
	
	//armement du handler de signal SIGCHLD
	struct sigaction newact;
	newact.sa_handler = sighandler;
	ret = sigemptyset(&newact.sa_mask);
	checkNeg(ret, "erreur sigemptyset");
	newact.sa_flags = 0;

	ret = sigaction(SIGCHLD, &newact, NULL);
	checkNeg(ret, "error sigaction");
	
	pid_t pid = fork_and_run(childHandler, NULL);
	while(1){
		sleep(1);
		printf("Le père envoie le signal SIGUSR1 à son fils\n");
		ret = kill(pid, SIGUSR1);
		checkNeg(ret, "error kill SIGUSR1");	
	}
}