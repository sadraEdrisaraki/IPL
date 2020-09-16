#include <stdio.h>
#include <stdlib.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#include "utils.h"

#include <unistd.h>

#define KEY 369
#define PERM 0666

int* z;
int shm_id;

//******************************************************************************
//INIT SHARED MEMORY
//******************************************************************************
void init_shm() {
  shm_id = shmget(KEY, sizeof(int), IPC_CREAT | PERM);
  checkNeg(shm_id, "Error shmget");
  
  z = shmat(shm_id, NULL, 0);
  checkCond(z == (void*) -1, "Error shmat");
}

//******************************************************************************
//RESET SHARED MEMORY
//******************************************************************************
void sshmdt() {
  int r = shmdt(z);
  checkNeg(r, "Error shmdt");
}

void del_shm() {
  int r = shmctl(shm_id, IPC_RMID, NULL);
  checkNeg(r, "Error shmctl");
}


//******************************************************************************
//CHILD HANDLER
//******************************************************************************
void child_handler() {
  init_shm();
  printf("*z = %d\n", *z);
  *z = 987654321;
  sshmdt();
}

//******************************************************************************
//MAIN FUNCTION
//******************************************************************************
int main (int argc, char *argv[]) {
  pid_t cpid = fork_and_run0(&child_handler);
  swaitpid(cpid, NULL, 0);
  
  init_shm();
  printf("*z = %d\n", *z);
  sshmdt();

  //COMMENT OR UNCOMMENT
  //del_shm();

  return 0;
}




 