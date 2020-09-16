#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/sem.h>
#include <string.h>

#include "utils.h"

#define KEY_SHM 2222
#define KEY_SEM 1919
#define PERM 0666
#define MAX 10

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
	if(argc!=2){
		printf("Usage : %s string\n", argv[0]);
		exit(0);
	}
	if(strlen(argv[1])>MAX){
		printf("Veuillez introduire un mot valide(max 10 caractères)\n");
		exit(22);
	}
	char *ptrMemPartagee;

	int id = shmget(KEY_SHM, sizeof(int), IPC_CREAT | PERM);
	checkNeg(id, "Error shmget");

	ptrMemPartagee = (char*)shmat(id, NULL, 0);
	checkCond(ptrMemPartagee == (void*) -1, "Error shmat");

	idSem = semget(KEY_SEM, 1, IPC_CREAT | PERM);
	checkNeg(idSem, "error semget");

	union semun arg;
	arg.val = 1;

	int rv = semctl(idSem, 0, SETVAL, arg);
	checkNeg(rv, "error semctl");

	//1e etape
	strcpy(ptrMemPartagee, argv[1]);
	down();
	//Attendre un peu pour exécuter le serveur
	sleep(1);
	up();

	//3e etape
	down();
	printf("%s\n", ptrMemPartagee);
	up();
	int rs = shmdt(ptrMemPartagee);
	checkNeg(rs, "error shmdt");

	int ret = shmctl(id, IPC_RMID, NULL);
	checkNeg(ret, "error shmctl");

	int res = semctl(idSem, 0, IPC_RMID);
	checkNeg(res, "error semctl");
}