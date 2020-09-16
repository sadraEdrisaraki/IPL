#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include "check.h"
#include "fork.h"

#define BUFFER 10

void sighandler(int signum){
	printf("Signal %d (%s)\n", signum, sys_siglist[signum]);
}

int main(int argc, char** argv){
	int ret;
	struct sigaction newact;
	newact.sa_handler = sighandler;
	newact.sa_flags = 0;
	ret = sigemptyset(&newact.sa_mask);
	checkNeg(ret, "error sigemptyset");

	for(int i = 1; i<=15; i++){
		//Probleme si on met SIGKILL en paramètre dans sigaction
		if(i==9){
			i++;
		}
		ret = sigaction(i, &newact, NULL);
		checkNeg(ret, "error sigaction");
	}

	printf("I am process %d\n", getpid());
	printf("appel read()\n");
	char buffer[BUFFER];
	while(1){
		read(0, buffer, BUFFER);
		if(errno == EINTR){
			printf("read() interrompu\n");
		}
		printf("appel read()\n");
	}	
}