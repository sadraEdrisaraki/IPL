#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h>
#include "utils.h"

#define N 255

void sigpipe_handler(){
	printf("--> Signal SIGPIPE reçu: problème de open/close pipe\n");
	exit(0);
}

void run(void *argv) {
  int *pipefd = argv;
	
  sclose(pipefd[1]);
  sclose(pipefd[0]);

  int nbChar;
  char ligne[N];
  while((nbChar = sread(pipefd[0], ligne, N))!=0){
  	for(int i=0; i<nbChar-1; i++){
  		if(ligne[i]>='a' && ligne[i]<='z'){
  			ligne[i]=ligne[i]-32;
  		}
  		nwrite(1, &ligne[i], sizeof(char));
  	}
  	printf("\n");
  }
  sclose(pipefd[0]);
}

int main(int argc, char **argv){
	int ret;
	struct sigaction newact;
	newact.sa_handler = sigpipe_handler;
	newact.sa_flags = 0;
	ret = sigemptyset(&newact.sa_mask);
	checkNeg(ret, "Error sigemptyset");

	ret = sigaction(SIGPIPE, &newact, NULL);
	checkNeg(ret, "error sigaction");

	int pipefd[2];
	spipe(pipefd);

	fork_and_run(run, pipefd);

	sclose(pipefd[0]);

	char ligne[N];
	size_t nbChar = sread(0, ligne, N);
	while(nbChar > 0){
		nwrite(pipefd[1], ligne, nbChar);
		nbChar = sread(0, ligne, N);
	}
	
	sclose(pipefd[1]);

	return 0;
}