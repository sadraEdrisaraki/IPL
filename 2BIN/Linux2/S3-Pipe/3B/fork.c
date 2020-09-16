#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/types.h>

#include "check.h"
#include "fork.h"

pid_t fork_and_run(void (*run)(void *, void *), void* arg0, void* arg1) {
  int childId = fork();
  checkNeg(childId, "Fork failded");

  if (childId == 0) {
    (*run)(arg0, arg1);
    exit(EXIT_SUCCESS);
  }
  
  return childId;
}

pid_t swaitpid(pid_t pid, int* status, int options) {
  pid_t waitId = waitpid(pid, status, options);
  checkNeg(waitId, "Error WAITPID");
  return waitId;
}