#include <stdio.h>
#include <stdlib.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#include "utils.h"

#include <unistd.h>

#define KEY 369
#define PERM 0666 // Permissions

/* Variable Globale */
int *z; // pointeur vers la variable partagé
int shm_id; // Id de la mémoire partagé

//******************************************************************************
//INIT SHARED MEMORY
//******************************************************************************

void init_shm() {
	shm_id = shmget(KEY, sizeof(int), IPC_CREAT | PERM); // créer ou renvoie l'id du segment
	checkNeg(shm_id, "Error shmget");

	// Attachement du segment
	z = shmat(shm_id, NULL, 0); // z pointe vers la case mémoire précédemment créer
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
	// controle du segment
	int r = shmctl(shm_id, IPC_RMID, NULL); // marquer le segment pour être détruit. Il ne sera qu'après le dernier détachement
	checkNeg(r , "Error shmctl");
}


int main(int argc, char const *argv[])
{
	init_shm();
	for (int i = 0; i < 20; ++i)
	{
		printf("%d\n", *z);
		sleep(5);
	}
	sshmdt();	
	return 0;
}