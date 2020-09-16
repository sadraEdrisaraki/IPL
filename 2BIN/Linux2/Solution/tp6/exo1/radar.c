#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#include "utils.h"

#define KEY 369
#define PERM 0666
#define TIMER 60
int signum;

void sigalarm_handler(int sig){
	signum = sig;
}

int main(int argc, char **argv){
	//Memoire partagee
	int* pointeurMemPartagee;

	//Création de la mémoire
	int id = shmget(KEY, sizeof(int), IPC_CREAT | PERM);
	checkNeg(id, "Error shmget");

	//Pointeur
	pointeurMemPartagee = shmat(id, NULL, 0);
	checkCond(pointeurMemPartagee == (void*) -1, "Error shmat");
	//*pointeurMemPartagee = 3;
	
	struct sigaction newact;
	newact.sa_handler = sigalarm_handler;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = 0;
	int resultat = sigaction(SIGALRM, &newact, NULL);
	checkNeg(resultat, "error sigaction");
	alarm(TIMER);

	while(signum != SIGALRM){
		int random = rand();
		printf("%d\n", random);
		*pointeurMemPartagee = random;
		sleep(3);
	}
	int ret = shmdt(pointeurMemPartagee);
	checkNeg(ret, "Error shmdt");
	
	int res = shmctl(id, IPC_RMID, NULL);
	checkNeg(res, "Error shmctl");
}