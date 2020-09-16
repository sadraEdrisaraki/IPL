#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils.h"

#define MAX_SIZE  1024

// PRE:  "buf" points to a memory segment such that the size of this 
//       memory segment is at least "count" bytes.

// POST: The first "count" bytes of buf are translated into 
//       their uppercase equivalent character
void toupper2(char *buf, size_t count) {
	for(int i = 0; i != count; i++) {
		buf[i] = toupper(buf[i]);
	}
}

void run(void *argv) {
	int *pipefd = argv;
	
	sclose(pipefd[1]);
	
	char buf[MAX_SIZE];
	ssize_t count = sread(pipefd[0], buf, MAX_SIZE);
	while(count > 0) {
		toupper2(buf, count);
		nwrite(1, buf, count);
		count = sread(pipefd[0], buf, MAX_SIZE);
	}
	
	sclose(pipefd[0]);
}

int main(int argc, char **argv){
	/* create pipe */
	int pipefd[2]; 
	spipe(pipefd);

  fork_and_run(run, pipefd);
	
	sclose(pipefd[0]);
	
	char buf[MAX_SIZE];
	size_t count = sread(0, buf, MAX_SIZE);
	while(count > 0) {
		nwrite(pipefd[1], buf, count);
		count = sread(0, buf, MAX_SIZE);
	}
	
	sclose(pipefd[1]);
	return 0;
}

