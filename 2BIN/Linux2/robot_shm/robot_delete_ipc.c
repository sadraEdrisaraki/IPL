#include "gen.h"
#include "utils.h"

#include <sys/ipc.h>


//******************************************************************************
// MAIN FUNCTION
//******************************************************************************
int main (int argc, char *argv[]) {

	int shm_id;
	init_shm(SHM_KEY,0, 0, &shm_id); // récupère la mémoire partagée 
	sshmdelete(shm_id); // delete

	int sem_id = ssemget(SEM_KEY, 0, 0);
	ssemdelete(sem_id); // delete semaphore

	return 0;
}