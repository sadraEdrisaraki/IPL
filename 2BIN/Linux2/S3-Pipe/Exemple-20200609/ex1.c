#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "check.h"
#include "fork.h"


void run(void *argv) {
  int *pipefd = argv;
	
  int ret = close(pipefd[1]);
  checkNeg(ret, "close error");
  
  int intVal;
  int nbChar = read(pipefd[0], &intVal, sizeof(int));
  checkCond(nbChar != sizeof(int), "read error");
  
  printf("entier reçu de mon père: %i\n", intVal);
  
  ret = close(pipefd[0]);
  checkNeg(ret, "close error");
}

int main(int argc, char **argv){
  /* create pipe */
  int pipefd[2]; 
  int ret = pipe(pipefd);
  checkNeg(ret, "pipe error");
	
  fork_and_run(run, pipefd);
  
  ret = close(pipefd[0]);
  checkNeg(ret, "close error");
	
  int intVal = 7;
  int nbChar = write(pipefd[1], &intVal, sizeof(int));
  checkCond(nbChar != sizeof(int), "write error");
	
  ret = close(pipefd[1]);
  checkNeg(ret, "close error");
	
  return 0;
}

