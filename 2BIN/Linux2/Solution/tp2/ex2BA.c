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
	
	int childId = fork();
	checkCond(childId == -1, "Fork failed");
	if(childId != 0){
		char *msg = "1 2 3\n";
		int res = write(1, msg, strlen(msg));
		checkCond(res == -1, "Error writing");
	}else{
		char *msg = "4 5 6\n";
		int res = write(1, msg, strlen(msg));
		checkCond(res == -1, "Error writing");
	}
}