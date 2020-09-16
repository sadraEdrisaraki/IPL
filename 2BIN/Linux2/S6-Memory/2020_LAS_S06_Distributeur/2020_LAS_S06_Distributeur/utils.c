#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "utils.h"



//*****************************************************************************
// CHECK
//*****************************************************************************

void checkCond(bool cond, char* msg) {
  if (cond) {
    perror(msg);
    exit(EXIT_FAILURE);
  }  
}

void checkNeg(int res, char* msg) {
  checkCond(res < 0, msg);
}

void checkNull(void* res, char* msg) {
  checkCond(res == NULL, msg);
}

//*****************************************************************************
// FORK
//*****************************************************************************

pid_t fork_and_run0(void (*run)(void)) {
  int childId = fork();
  checkNeg(childId, "Fork failded");

  if (childId == 0) {
    (*run)();
    exit(EXIT_SUCCESS);
  }
  
  return childId;
}

pid_t fork_and_run1(void (*run)(void *), void* arg0) {
  int childId = fork();
  checkNeg(childId, "Fork failded");

  if (childId == 0) {
    (*run)(arg0);
    exit(EXIT_SUCCESS);
  }
  
  return childId;
}

pid_t fork_and_run2(void (*run)(void *, void *), void *arg0, void *arg1) {
  int childId = fork();
  checkNeg(childId, "Fork failded");

  if (childId == 0) {
    (*run)(arg0, arg1);
    exit(EXIT_SUCCESS);
  }
  
  return childId;
}

pid_t fork_and_run3(void (*run)(void *, void *, void *), void* arg0, void *arg1, void *arg2) {
  int childId = fork();
  checkNeg(childId, "Fork failded");

  if (childId == 0) {
    (*run)(arg0, arg1, arg2);
    exit(EXIT_SUCCESS);
  }
  
  return childId;
}

pid_t swaitpid(pid_t pid, int* status, int options) {
  pid_t waitId = waitpid(pid, status, options);
  checkNeg(waitId, "Error WAITPID");
  return waitId;
}

int sclose(int fd) {
  int resv = close(fd);
  checkNeg(resv, "Error CLOSE");
  return resv;
}

ssize_t sread(int fd, void *buf, size_t count) {
  ssize_t r = read(fd, buf, count);
  checkNeg(r , "Error WRITE");
  return r;
}

ssize_t swrite(int fd, const void *buf, size_t count) {
  ssize_t r = write(fd, buf, count);
  checkNeg(r , "Error WRITE");
  return r;
}

void nwrite(int fd, const void* buf, size_t count) {
  char* cbuf = (char*) buf;
  int s = swrite(fd, cbuf, count);
  int i = s;
  while(s != 0 && i != count) {
    i += s;
    s =  swrite(fd, cbuf + i, count - i);
  }

  if (i != count) {
    fprintf(stderr, "Unable to write %lu byte(s)\n", count);
    exit(EXIT_FAILURE);
  } 
}


//*****************************************************************************
// PIPE
//*****************************************************************************
int spipe(int pipefd[2]) {
  int resv = pipe(pipefd);
  checkNeg(resv, "Error PIPE");
  return resv;
}

//*****************************************************************************
// SIGNAL
//*****************************************************************************

void ehandler(int signum) {
}

void ssigaction(int signum, void (*handler)(int signum)) {
  struct sigaction action;
  action.sa_handler = handler;
  ssigfillset(&action.sa_mask);
  action.sa_flags = 0;
  
  int r = sigaction (signum, &action, NULL);
  checkNeg(r, "Error sigaction");
}

void ssigemptyset(sigset_t *set) {
  int res = sigemptyset(set);
  checkNeg(res, "sigemptyset");
}

void ssigfillset(sigset_t *set) {
  int res = sigfillset(set);
  checkNeg(res, "sigfillset");
}

void ssigaddset(sigset_t *set, int signum) {
  int res = sigaddset(set, signum);
  checkNeg(res, "sigaddset");
}

void ssigdelset(sigset_t *set, int signum) {
  int res = sigdelset(set, signum);
  checkNeg(res, "sigdelset");
}

void ssigprocmask(int how, const sigset_t *set, sigset_t *oldset) {
  int res = sigprocmask(how, set, oldset);
  checkNeg(res, "sigprocmask");
}

void skill(pid_t pid, int signum) {
  int res = kill(pid, signum);
  checkNeg(res, "kill");
}

void ssigpending(sigset_t *set) {
  int ret = sigpending(set);
  checkNeg(ret, "ssigpending");
}

//******************************************************************************
// SHARED MEMORY
//******************************************************************************
void* init_shm(key_t key, size_t size, int shmflg, int *shm_id) {
  *shm_id = shmget(key, size, shmflg);
  checkNeg(*shm_id, "Error shmget");
  
  void *res = shmat(*shm_id, NULL, 0);
  checkCond(res == (void*) -1, "Error shmat");
  return res;
}

int sshmdt(const void *shmaddr) {
  int res = shmdt(shmaddr);
  checkNeg(res, "Error shmdt");
  return res;
}

void sshmdelete(int shm_id) {
  int r = shmctl(shm_id, IPC_RMID, NULL);
  checkNeg(r, "Error shmctl");
}

//******************************************************************************
//SEMAPHORES
//******************************************************************************
int ssemget(key_t key, int nsems, int semflg) {
  int sem_id = semget(key, nsems, semflg);
  checkNeg(sem_id, "Error semget");
  return sem_id;
}

void ssem_setval(int sem_id, int sem_num, int val) {
  union semun arg; 
  arg.val = val;
  
  int rv = semctl(sem_id, sem_num, SETVAL, arg);
  checkNeg(rv, "Error semctl");
}

void ssem_add(int sem_id, int sem_num, int val) {
  struct sembuf sem; 
  sem.sem_num = sem_num; 
  sem.sem_op = val; 
  sem.sem_flg = 0;

  int rc = semop(sem_id, &sem, 1);
  checkNeg(rc, "Error semop");
}

void sdown(int sem_id, int sem_num) {
  ssem_add(sem_id, sem_num, -1);
}

void sup(int sem_id, int sem_num) {
  ssem_add(sem_id, sem_num, 1);
}

void ssemdelete(int sem_id) {
  int rv = semctl(sem_id, 0, IPC_RMID);
  checkNeg(rv, "Error semctl");
}