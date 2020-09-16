#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/sem.h>

#include "utils.h"

#define KEY_SHM 1922
#define KEY_SEM 2219
#define PERM 0666

int idSem;

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

	int rc = semop(idSem, &sem, 1);
	checkNeg(rc, "error semop");
}

void down(){
	add_sem(-1);
}

void up(){
	add_sem(1);
}

int main(int argc, char **argv){
	int *ptrMemPartagee;

	int id = shmget(KEY_SHM, sizeof(int), IPC_CREAT | PERM);
	checkNeg(id, "Error shmget");

	ptrMemPartagee = shmat(id, NULL, 0);
	checkCond(ptrMemPartagee == (void*) -1, "Error shmat");

	idSem = semget(KEY_SEM, 1, IPC_CREAT | PERM);
	checkNeg(idSem, "error semget");

	union semun arg;
	arg.val = 1;

	int rv = semctl(idSem, 0, SETVAL, arg);
	checkNeg(rv, "error semctl");

	down();
	printf("%d\n", ptrMemPartagee[1]);
	ptrMemPartagee[1]++;
	up();
	shmdt(ptrMemPartagee);
}