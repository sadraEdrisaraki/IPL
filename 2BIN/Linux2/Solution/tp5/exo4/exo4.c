#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include "utils.h"

sig_atomic_t signum;
int frequence;
int nbSignaux;
int cpt = 0;

void sighandler(int sig){
	signum = sig;
}

void childHandler(void* argv){
	ssigaction(SIGUSR1, &sighandler);
	ssigaction(SIGUSR2, &sighandler);

	sigset_t set;
	ssigfillset(&set);
	ssigdelset(&set, SIGUSR1);

	char** arg = argv;

	for(int i = 0; i<frequence; i++){
		for(int j = 2; j<nbSignaux; j++){
			skill(getppid(), atoi(arg[j]));
			sigsuspend(&set);
		}
	}

	skill(getppid(), SIGKILL);
	exit(EXIT_SUCCESS);

}

int main(int argc, char **argv){

	if(argc < 3){
		printf("Usage : %s frequence signal [signal] ... [signal]\n", argv[0]);
		exit(0);
	}
	
	sigset_t newset;	
	ssigfillset(&newset);
	ssigprocmask(SIG_BLOCK, &newset, NULL);

	sigset_t set;
	ssigfillset(&set);

	frequence = atoi(argv[1]);
	nbSignaux = argc;

	pid_t childId = fork_and_run1(childHandler, argv);
	// armement des signaux; les signaux qu'il va recevoir
	for(int i = 2; i<argc; i++){
		ssigaction(atoi(argv[i]), &sighandler);
		ssigdelset(&set, atoi(argv[i]));
	}
	
	sigsuspend(&set);
	int cpt = 1;
	while(1){
		printf("%d - Signal %d reçu (%s)\n", cpt, signum, sys_siglist[signum]);	
		skill(childId, SIGUSR1);
		if(signum == atoi(argv[argc-1])){
			cpt++;
		}
		sigsuspend(&set);
	}
}