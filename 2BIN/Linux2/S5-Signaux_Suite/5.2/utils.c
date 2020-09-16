#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

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

//*****************************************************************************
// IO
//*****************************************************************************
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

/* Armement d'un handler */
void ssigaction(int signum, void (*handler)(int signum)) {

  struct sigaction action;
  action.sa_handler = handler;
  ssigfillset(&action.sa_mask);
  action.sa_flags = 0;
  
  int r = sigaction (signum, &action, NULL);
  checkNeg(r, "Error sigaction");
}

/* Vide l'ensemble de signaux */
void ssigemptyset(sigset_t *set) {
  int res = sigemptyset(set);
  checkNeg(res, "sigemptyset");
}

/* Remplit l'ensemble de signaux --> tous les signaux qui existe*/
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