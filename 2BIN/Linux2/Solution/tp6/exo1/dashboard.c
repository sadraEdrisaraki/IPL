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
	int* pointeurMemPartagee;

	int id = shmget(KEY, sizeof(int), IPC_CREAT | PERM);
	checkNeg(id, "Error shmget");

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
		printf("%d\n", *pointeurMemPartagee);
		sleep(5);
	}
	
	int ret = shmdt(pointeurMemPartagee);
	checkNeg(ret, "Error shmdt");
}