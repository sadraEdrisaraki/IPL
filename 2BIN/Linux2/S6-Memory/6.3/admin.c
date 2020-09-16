#include <stdio.h>
#include <stdlib.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#include "utils.h"

#include <unistd.h>

#define SHM_KEY 248
#define SEM_KEY 888
#define PERM 0666 // Tout le monde peut lire/ecrire

#define SIZE_TAB 2

//******************************************************************************
//VARIABLE GLOBALE
//******************************************************************************

int *z;
int shm_id; // Id de la mémoire partagé
int sem_id;

union semun {
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
};

//******************************************************************************
//INIT SHARED MEMORY
//******************************************************************************
void init_shm() {
  // si la mémoire n'existe pas il la crée
  shm_id = shmget(SHM_KEY, sizeof(int)*SIZE_TAB, IPC_CREAT | PERM);
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
  // Supprime si plus personnes attachés 
  int r = shmctl(shm_id, IPC_RMID, NULL);
  checkNeg(r , "Error shmctl");
}

//******************************************************************************
//SEMAPHORE
//******************************************************************************
void init_sem(int val) {
  
  // CREATE A SET OF ONE SEMAPHORE.
  // THE NUMBER ASSOCIATED WITH THIS SEMAPHORE IS 0.
  sem_id = semget(SEM_KEY, 1, IPC_CREAT | PERM);
  checkNeg(sem_id, "Error semget");

  // INIT THE SEMAPHORE VALUE TO val
  union semun arg; 
  arg.val = val;
  
  int rv = semctl(sem_id, 0, SETVAL, arg);
  checkNeg(rv, "Error semctl");
}

void add_sem(int val) {
  struct sembuf sem; 
  sem.sem_num = 0; 
  sem.sem_op = val; 
  sem.sem_flg = 0;

  int rc = semop(sem_id, &sem, 1);
  checkNeg(rc, "Error semop");
}

void down() {
  add_sem(-1);
}

void up() {
  add_sem(1);
}

void del_sem() {
  int rv = semctl(sem_id, 0, IPC_RMID);
  checkNeg(rv, "Error semctl");
}


int main(int argc, char const *argv[])
{
  return 0;
}