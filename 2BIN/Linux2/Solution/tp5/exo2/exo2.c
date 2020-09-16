#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include "utils.h"

#define N 255

int cpt = 1;
int cptSigint = 0;
int signum;
pid_t pid;
int x;
int r;
bool enPause = false;

void sighandler(int num){
	signum = num;
}

/** Méthode executer par le processus fils */
void run(void* argv, void* argv2){
	x = atoi(argv);
	r = atoi(argv2);

	ssigaction(SIGUSR1, sighandler);

	int cpt = 1;
	while(1){
		printf("%d, ", x+(cpt*r));
		cpt++;
		if(signum == SIGUSR1){
			printf("\nFils : valeur de n (%d) et calcul (%d + %d * %d).\n", cpt, x, cpt, r);
			signum = 0;
		}
		struct timespec t;
		t.tv_sec = 0;        
		t.tv_nsec = 50000000;
		nanosleep(&t,NULL);
	}
}

int main(int argc, char **argv){
	if(argc != 3){
		printf("Usage : %s nombre1 nombre2\n", argv[0]);
		exit(0);
	}

	ssigaction(SIGQUIT, sighandler);
	ssigaction(SIGTSTP, sighandler);
	ssigaction(SIGINT, sighandler);
	ssigaction(SIGALRM, sighandler);

	pid = fork_and_run2(run, argv[1], argv[2]);

	while(1){
		if(signum == SIGQUIT){
			printf("\nPère : envoie-moi l'état du calcul, fiston.\n");
			skill(pid, SIGUSR1);
			signum = 0;
		}
		if(signum == SIGTSTP){
			if(!enPause){
				skill(pid, SIGSTOP);
				enPause = true;
			}else{
				skill(pid, SIGCONT);
				enPause = false;
			}
			signum = 0;
		}
		if(signum == SIGINT){
			if(cptSigint == 0){
				alarm(1);
			}
			cptSigint++;
			signum = 0;
		}	
		if(signum == SIGALRM){
			if(cptSigint>=2){
				skill(pid, SIGUSR1);
				sleep(1);
				skill(pid, SIGKILL);
				printf("Fin du programme\n");
				exit(19);
			}else{
				cptSigint=0;
				signum = 0;
			}
		}
	}
}