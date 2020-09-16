#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#include "utils.h"


/* Variable globale */
int signum;
int countSIGINT = 0; 
bool enPause = false;

/* Gestionnaire des signaux : il doit faire le moins de chose possible */
void sig_handler (int sig) {
	signum = sig;
}

/* Excecuter par le processus fils */ 
void run(void *argv1, void *argv2){
	int r = atoi(argv1);
	int x = atoi(argv2);

	ssigaction(SIGUSR1, sig_handler);

	int count = 0;
	while(1) {
		printf("%d", x + (count*r));
		count++;
		// Gestion signal
		if (signum == SIGUSR1) {
			printf("\nFils : valeur de n (%d) et calcul (%d + %d * %d).\n", count, x, count, r);
			signum = 0;
		}
		// Pour pas allez trop vite 
		sleep(5);
	}
}


int main(int argc, char *argv[])
{
	if (argc != 3) {
		printf("Usage : %s nombre1 nombre2\n", argv[0]);
		exit(0);
	}

	/* Armement des signaux : si on reçoit un de ces signaux on le gère grace au handler*/
	ssigaction(SIGQUIT, sig_handler);
	ssigaction(SIGTSTP, sig_handler);
	ssigaction(SIGINT, sig_handler);
	ssigaction(SIGALRM, sig_handler);

	pid_t pid = fork_and_run2(run, argv[1], argv[2]);

	/* Père */
	while(1) {
		/* Gère les signaux reçu */
		switch (signum) {
			case SIGQUIT:
				printf("\nJe suis le père : envoie-moi l'état du calcul, fistion.\n");
				skill(pid, SIGUSR1); // envoie du signal;
				signum = 0;
				break;
			case SIGTSTP:
				// endort ou réveille le processus fils
				if (!enPause) {
					skill(pid, SIGSTOP);
					enPause = true;
				} else {
					skill(pid, SIGCONT);
					enPause = false;
				}
				signum = 0;
				break;
			case SIGINT:
				if (countSIGINT == 0) {
					alarm(1); // envoie un signal après 1 sec.
				} 
				countSIGINT++;
				signum = 0;
				break;
			case SIGALRM:
				alarm(0);
				if (countSIGINT >= 2) {
					skill(pid, SIGUSR1);
					sleep(1);
					skill(pid, SIGKILL);
					printf("Fin du programme\n");
					exit(EXIT_SUCCESS);
				} else {
					countSIGINT = 0;
					signum = 0;
				}
				break;
			default:
				break;
		}
	}

	return 0;
}