#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

void checkCond(bool cond, char *msg){
	if(cond){
		perror(msg);
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char **argv){
	int childId = fork();
	checkCond(childId == -1, "Fork failed");
	if(childId != 0){
		int status;
		int waitId = waitpid(childId, &status, 0);
		checkCond(waitId == -1, "Wait error");
		char *msg = "1 2 3\n";
		int res = write(1, msg, strlen(msg));
		checkCond(res == -1, "Error writing");
		checkCond(waitId != childId, "This should not happen");
		printf("Exit status child: %d\n", WEXITSTATUS(status));
	}else{
		char *msg = "4 5 6\n";
		int res = write(1, msg, strlen(msg));
		checkCond(res == -1, "Error writing");
		exit(19);
	}
}