#include <stdio.h>

#include "gen.h"
#include "utils.h"

//******************************************************************************
// MAIN FUNCTION
//******************************************************************************
int main (int argc, char *argv[]) {
  int shm_id; 
  int *nums = init_shm(SHM_KEY, 0, 0, &shm_id);
  
  int sem_id = ssemget(SEM_KEY, 0, 0);
  
  sdown(sem_id, 0);
  if (nums[0] < nums[1]) {
    printf("%d\n", nums[0]);
    nums[0]++;
  } else {
    printf("Il n’y a plus personne!\n");
  }
  sup(sem_id, 0);
  
  sshmdt(nums);
  return 0;  
}