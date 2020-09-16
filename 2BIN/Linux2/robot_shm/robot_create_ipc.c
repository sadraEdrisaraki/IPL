#include "gen.h"
#include "utils.h"

#include <sys/ipc.h>

//******************************************************************************
// MAIN FUNCTION
//******************************************************************************
int main (int argc, char *argv[]) {
	int shm_id; // Id de la mémoire partagée
	int *coordonnees = init_shm(SHM_KEY, sizeof(int)*2, IPC_CREAT | IPC_EXCL | PERM, &shm_id);
	coordonnees[0] = 0;
	coordonnees[1] = 0;
	sshmdt(coordonnees); // détachement après la création

	int sem_id = ssemget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | PERM); 
	ssem_setval(sem_id, 0, 1);


	return 0;
}