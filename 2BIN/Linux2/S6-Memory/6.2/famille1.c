#include <stdio.h>
#include <stdlib.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include<sys/wait.h> 
#include <sys/sem.h>


#include "utils.h"

#include <unistd.h>

#define NB_MESSAGE 3

#define SHM_KEY 248 // la clé de la mémoire partagé 
#define SEM_KEY 369 // la clé du sémaphore
#define PERM 0666

union semun {
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
};

int sem_id;

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


void child_run(void ) {
	down();
	for (int i = 0; i < NB_MESSAGE; ++i)
	{	
		
		printf("Je suis le fils : %d\n", getpid());
		sleep(1);
		
	}
	up();
}

int main(int argc, char const *argv[])
{

	init_sem(1);

	fork_and_run0(child_run);
	fork_and_run0(child_run);

	wait(NULL);
	wait(NULL);

	return 0;
}