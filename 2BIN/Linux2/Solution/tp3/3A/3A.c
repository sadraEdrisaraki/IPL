#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "check.h"
#include "fork.h"

#define N 255

void run(void *argv) {
  int *pipefd = argv;
	
  int ret = close(pipefd[1]);
  checkNeg(ret, "close error");
  
  int nbChar;
  char ligne[N];
  while((nbChar = read(pipefd[0], &ligne, N))!=0){
  	for(int i=0; i<nbChar-1; i++){
  		if(ligne[i]>='a' && ligne[i]<='z'){
  			ligne[i]=ligne[i]-32;
  		}
  		write(1, &ligne[i], sizeof(char));
  	}
  	printf("\n");
  }
  ret = close(pipefd[0]);
  checkNeg(ret, "close error");
}

int main(int argc, char **argv){
	int pipefd[2];
	int res = pipe(pipefd);
	checkNeg(res, "pipe failed");

	fork_and_run(run, pipefd);

	res = close(pipefd[0]);
	checkNeg(res, "close error");

	int nbChar;
	char ligne[N];
	while((nbChar = read(0, &ligne, N))!=0){
		int nbCharW = write(pipefd[1], &ligne, nbChar);
		checkCond(nbChar != nbCharW, "write error");
	}
	
	res = close(pipefd[1]);
	checkNeg(res, "close error");

	return 0;
}