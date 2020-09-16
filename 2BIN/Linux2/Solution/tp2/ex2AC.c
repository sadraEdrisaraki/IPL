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
	char *msg = "trois .. deux .. un ..\n";
	write(1, msg, strlen(msg));
	int childId = fork();
	checkCond(childId == -1, "Fork failed");
	if(childId == 0){
		msg = "partez !\n";
		write(1, msg, strlen(msg));
	}
}