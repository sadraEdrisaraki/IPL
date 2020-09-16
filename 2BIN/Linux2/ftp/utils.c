#include "utils.h"
#include <wait.h>
#include <string.h>

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


pid_t fork_and_run(void (*run)(char *), char * arg0) {
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

int sopen(char* path, int flag, int mode) {
  int fd = open(path, flag, mode);
  checkNeg(fd, "Error OPEN");
  return fd;
}

void swrite(int fd, void* buff, int size) {
  int r = write(fd, buff, size);
  checkCond(r != size, "Error WRITE");
}

int sread(int fd, void* buff, int size) {
  int r = read(fd, buff, size);
  checkNeg(r, "Error READ");
  return r;
}

void sclose(int fd) {
  int r = close(fd);
  checkNeg(r, "Error CLOSE");
}

