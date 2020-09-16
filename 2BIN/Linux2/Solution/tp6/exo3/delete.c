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

union semun {
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
};

int main(int argc, char **argv){
	int *ptrMemPartagee;

	int id = shmget(KEY_SHM, sizeof(int), IPC_CREAT | PERM);
	checkNeg(id, "Error shmget");

	ptrMemPartagee = shmat(id, NULL, 0);
	checkCond(ptrMemPartagee == (void*) -1, "Error shmat");

	//Indice 0 indique le prochain numéro à apparaître dans l'écran
	ptrMemPartagee[0] = 1;

	//Indice 1 indique le prochain numéro dans le distributeur
	ptrMemPartagee[1] = 1;
	shmdt(ptrMemPartagee);

	int idSem = semget(KEY_SEM, 1, IPC_CREAT | PERM);
	checkNeg(idSem, "error semget");

	union semun arg;
	arg.val = 1;

	int rv = semctl(idSem, 0, SETVAL, arg);
	checkNeg(rv, "error semctl");

	int del1 = shmctl(id, IPC_RMID, NULL);
	checkNeg(del1, "error shmctl");

	int del2 = semctl(idSem, 0, IPC_RMID);
	checkNeg(del2, "error semctl");

}