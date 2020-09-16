#include <stdio.h>
#include <stdlib.h>
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
	char *msg = "trois .. deux .. un ..";
	int res = write(1, msg, strlen(msg));
	checkCond(res == -1, "Error writing");
	int childId = fork();
	checkCond(childId == -1, "Fork failed");
	if(childId == 0){
		msg = "partez !";
		res = write(1, msg, strlen(msg));
		checkCond(res == -1, "Error writing");
	}
}