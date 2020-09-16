#include "gen.h"
#include "utils.h"

#include <sys/ipc.h>

//******************************************************************************
// MAIN FUNCTION
//******************************************************************************
int main (int argc, char *argv[]) {
  int id; 
  int *nums = init_shm(SHM_KEY, 2 * sizeof(int), IPC_CREAT | IPC_EXCL | PERM, &id);
  nums[0] = 1;
  nums[1] = 1;
  sshmdt(nums);
  
  id = ssemget(SEM_KEY, 1, IPC_CREAT|  IPC_EXCL | PERM);
  ssem_setval(id, 0, 1);
  return 0;
}