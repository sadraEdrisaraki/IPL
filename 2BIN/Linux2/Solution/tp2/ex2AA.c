#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

void checkCond(bool cond, char *msg){
	if(cond){
		perror(msg);
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char **argv){
	int a = 5;
	int childId = fork();
	checkCond(childId == -1, "Fork failed");
	if(childId != 0){
		int b = a*5;
		printf("parent = a: %d | b: %d\n", a, b);
	}else{
		int b = a*2;
		printf("enfant = a: %d | b: %d\n", a, b);
	}
}