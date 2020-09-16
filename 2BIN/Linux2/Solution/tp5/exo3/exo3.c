#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include "utils.h"

#define TIMER 5

int signum;

void sighandler(int num){
	signum = num;
}

void run(){
	/*Armement des signaux; ceux qu'on traite */
	ssigaction(SIGUSR1, sighandler);
	ssigaction(SIGUSR2, sighandler);

	sigset_t set; // masque de signaux
	ssigfillset(&set);
	
	ssigdelset(&set, SIGUSR1);
	ssigdelset(&set, SIGUSR2);
	sigsuspend(&set);

	int cpt = 0;
	while(signum != SIGUSR2){
		cpt++;
		suskill(getppid(), SIGUSR1);
		sigsuspend(&set);
	}

	printf("Fils : #SIGUSR1 SEND = %d\n", cpt);
}

int main(int argc, char **argv){
	sigset_t set1;
	ssigfillset(&set1);

	//Sigprocmask doit etre fait avant le fork
	//sigprocmask obligé pour bloquer tous les signaux; on bloque le temps que les processus mettents en place leur gestionnaire de signaux
	sigprocmask(SIG_BLOCK, &set1, NULL);

	ssigaction(SIGUSR1, sighandler);

	pid_t pid = fork_and_run0(run);
	ssigaction(SIGALRM, sighandler);
	alarm(TIMER);

	//Le programme est suspendu tant que le signal SIGUSR1 ou SIGALRM
	//n'a pas été reçu
	// bloque tous les signaux mise à part SIGUSR1 & SIGALRM
	sigset_t set2;
	ssigfillset(&set2);
	ssigdelset(&set2, SIGUSR1);
	ssigdelset(&set2, SIGALRM);

	//Envoie du 1er signal
	int cpt = 1;
	skill(pid, SIGUSR1);
	sigsuspend(&set2);
	// boucle tant qu'il na pas reçu un signal alarm
	while(signum != SIGALRM){
		printf("%s\n", "boucle while");
		cpt++;
		skill(pid, SIGUSR1);

		//Le programme est suspendu tant que le signal SIGUSR1 ou SIGALRM
		//n'a pas été reçu
		sigsuspend(&set2);
	}

	skill(pid, SIGUSR2);
	printf("Père : #SIGUSR1 SEND = %d\n", cpt);
	swaitpid(pid, NULL, 0);
}