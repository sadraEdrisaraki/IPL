#include "gen.h"
#include "utils.h"

#include <sys/ipc.h>

//******************************************************************************
// MAIN FUNCTION
//******************************************************************************
int main (int argc, char *argv[]) {
  int shm_id; 
  init_shm(SHM_KEY, 0, 0, &shm_id);
  sshmdelete(shm_id);
  
  int sem_id = ssemget(SEM_KEY, 0, 0);
  ssemdelete(sem_id);
  
  return 0;
}