#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#include "utils.h"

#define KEY 190
#define PERM 0666
#define TIMER 60

void childHandler(){
	pid_t myPid = getpid();
	int cpt = 3;
	while(cpt!=0){
		printf("je suis le fils %d\n", myPid);
		cpt--;
		sleep(1);	
	}
}

int main(int argc, char **argv){
	pid_t childId1 = fork_and_run0(childHandler);
	pid_t childId2 = fork_and_run0(childHandler);

	//On peut choisir un des deux
	swaitpid(childId1, NULL, 0);
	swaitpid(childId2, NULL, 0);
}