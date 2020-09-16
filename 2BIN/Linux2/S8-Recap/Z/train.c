#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

#include "check.h"

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

// A COMPLETER: inclure ici les "handlers" de signaux


//*****************************************************************************
// CHILD HANDLER
//*****************************************************************************
void child_handler() {
  // A COMPLETER: inclure ici le code du fils
}

//*****************************************************************************
// MAIN FUNCTION
//*****************************************************************************
int main (int argc, char *argv[]) {
    // A COMPLETER: inclure ici le code du père
  pid_t cid = fork_and_run(&child_handler);

  char buff[2];
  int res = sread(0, buff, 2);
  while(res != 0) {
    if (buff[0] == 'q') {
    } else {
    }
    res = sread(0, buff, 2);
  }

  swaitpid(cid, NULL);
}