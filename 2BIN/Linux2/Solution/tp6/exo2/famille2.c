#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/sem.h>

#include "utils.h"

#define KEY 190
#define PERM 0666

int id;

union semun {
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
};

void add_sem(int val){
	struct sembuf sem;
	sem.sem_num = 0;
	sem.sem_op = val;
	sem.sem_flg = 0;

	int rc = semop(id, &sem, 1);
	checkNeg(rc, "error semop");
}

void down(){
	add_sem(-1);
}

void up(){
	add_sem(1);
}

void childHandler(){
	pid_t myPid = getpid();
	int cpt = 3;
	down();
	while(cpt!=0){
		printf("je suis le fils %d\n", myPid);
		cpt--;
		sleep(1);	
	}
	up();
}

int main(int argc, char **argv){
	id = semget(KEY, 1, IPC_CREAT | PERM);
	checkNeg(id, "error semget");

	union semun arg;
	arg.val = 1;

	int rv = semctl(id, 0, SETVAL, arg);
	checkNeg(rv, "error semctl");

	fork_and_run0(childHandler);
	pid_t childId2 = fork_and_run0(childHandler);

	swaitpid(childId2, NULL, 0);

	int rs = semctl(id, 0, IPC_RMID);
  	checkNeg(rs, "Error semctl");
}