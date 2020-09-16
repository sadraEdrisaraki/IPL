#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

#include "check.h"

int signum;

//*****************************************************************************
// HELPER FUNCTIONS
//*****************************************************************************
int sread(int fd, void* buff, int size) {
  int r = read(fd, buff, size);
  checkNeg(r, "Error READ");
  return r;
}

pid_t fork_and_run(void (*handler)()) {
  int childId = fork();
  checkNeg(childId, "Error [fork_and_run]");
  
  // child process
  if (childId == 0) {  
    (*handler)();
    exit(EXIT_SUCCESS);
  }
  
  return childId;
}

void swaitpid(pid_t pid, int* status) {
  pid_t waitId = waitpid(pid, status, 0);
  checkNeg(waitId, "Error waitpid()");
}

//*****************************************************************************
// SIGNAL HANDLER
//*****************************************************************************

  void sighandler(int sig){
    signum = sig;
  }


//*****************************************************************************
// CHILD HANDLER
//*****************************************************************************
void child_handler() {
  int res;
  struct sigaction newact;
  newact.sa_handler = sighandler;
  newact.sa_flags = 0;
  res = sigemptyset(&newact.sa_mask);
  checkNeg(res, "error sigemptyset");

  res = sigaction(SIGUSR1, &newact, NULL);
  checkNeg(res, "error sigaction");

  res = sigaction(SIGUSR2, &newact, NULL);
  checkNeg(res, "error sigaction");

  res = sigaction(SIGQUIT, &newact, NULL);
  checkNeg(res, "error sigaction");

  int ret;
  sigset_t set;
  ret = sigfillset(&set);
  checkNeg(ret, "error set");
  ret = sigdelset(&set, SIGUSR1);
  checkNeg(ret, "error set");
  ret = sigdelset(&set, SIGUSR2);
  checkNeg(ret, "error set");
  ret = sigdelset(&set, SIGQUIT);
  checkNeg(ret, "error set");
  sigsuspend(&set);

  bool valide = true;
  bool quitteGare = false;
  while(signum != SIGQUIT){
    if(signum==SIGUSR1){
      if(!quitteGare){
        quitteGare = true;
      }else{
        valide = false;
      }
    }else{
      if(quitteGare){
        quitteGare = false;
      }else{
        valide = false;
      }
    }
    sigsuspend(&set);
  }

  if(valide && !quitteGare){
    printf("yes\n");
  }else{
    printf("no\n");
  }

  exit(EXIT_SUCCESS);

}

//*****************************************************************************
// MAIN FUNCTION
//*****************************************************************************
int main (int argc, char *argv[]) {
  int ret;
  sigset_t set;
  ret = sigemptyset(&set);
  checkNeg(ret, "error set");
  ret = sigaddset(&set, SIGUSR1);
  checkNeg(ret, "error set");
  ret = sigaddset(&set, SIGUSR2);
  checkNeg(ret, "error set");
  ret = sigaddset(&set, SIGQUIT);
  checkNeg(ret, "error set");

  ret = sigprocmask(SIG_BLOCK, &set, NULL);


  pid_t cid = fork_and_run(&child_handler);
  
  char buff[2];
  int res = sread(0, buff, 2);
  while(res != 0) {
    if (buff[0] == 'q') {
      ret = kill(cid, SIGUSR1);
      checkNeg(ret, "error kill SIGUSR1");
    } else if(buff[0] == 'e'){
      ret = kill(cid, SIGUSR2);
      checkNeg(ret, "error kill SIGUSR2");
    }
    sleep(1);
    res = sread(0, buff, 2);
  }

  ret = kill(cid, SIGQUIT);
  checkNeg(ret, "error kill SIGQUIT");

  swaitpid(cid, NULL);
}