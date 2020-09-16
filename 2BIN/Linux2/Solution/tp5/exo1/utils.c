#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

pid_t fork_and_run(void (*run)(void *), void* arg0) {
  int childId = fork();
  checkNeg(childId, "Fork failded");

  if (childId == 0) {
    (*run)(arg0);
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