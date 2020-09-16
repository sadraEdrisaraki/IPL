#include <stdio.h>
#include <stdlib.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#include "utils.h"

#include <unistd.h>

#define KEY 369
#define PERM 0666

/* Variable Globale */
int *z;
int shm_id; // Id de la mémoire partagé

//******************************************************************************
//INIT SHARED MEMORY
//******************************************************************************

void init_shm() {
	shm_id = shmget(KEY, sizeof(int), IPC_CREAT | PERM);
	checkNeg(shm_id, "Error shmget");

	// Attachement du segment
	z = shmat(shm_id, NULL, 0);
	checkCond(z == (void*) - 1, "Error shmat");
}

//******************************************************************************
//RESET SHARED MEMORY
//******************************************************************************
void sshmdt() {
	// Detachement du segment
	int r = shmdt(z);
	checkNeg(r, "Error shmdt");
}

void del_shm() {
	int r = shmctl(shm_id, IPC_RMID, NULL);
	checkNeg(r , "Error shmctl");
}


int main(int argc, char const *argv[])
{
	init_shm();
	for (int i = 0; i < 20; ++i)
	{
		printf("radar : Ecriture\n");
		(*z) = i;
		sleep(3);
	}

	sshmdt();

	return 0;
}