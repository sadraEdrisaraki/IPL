#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include "check.h"

#define MAX 20
#define SIZE 30

static pid_t fork_and_run(void(*handler)(char*), char* fn){
	pid_t pid = fork();
	if(pid == -1){
		perror("Fork failed.\n");
		exit(EXIT_FAILURE);
	}
	if(pid == 0){
		(*handler)(fn);
		exit(EXIT_SUCCESS);
	}
	return pid;
}

void executerLs(char *argv){
	execl("/bin/ls", "/bin/ls", "-l", argv, NULL);
}

void executerCat(char *argv){
	execl("/bin/cat", "/bin/cat", argv, NULL);
}

void executerExec(char *argv){
	execl(argv, argv, NULL);
}

int main(int argc, char **argv){
	int nbre;
	char fichier[MAX];
	nbre = read(0, fichier, MAX);
	checkNeg(nbre, "read file failed");
	fichier[nbre-1]='\0';

	int file = open(fichier, O_CREAT | O_TRUNC | O_WRONLY, 0660);
	checkNeg(file, "open failed");

	int retour=fchmod(file,0777);
	checkNeg(retour,"Error fchmod");

	fork_and_run(executerLs, fichier);

	char ligne[SIZE];
	while((nbre = read(0, ligne, SIZE)) > 0){
		checkNeg(nbre, "error reading");
		int taille = write(file, ligne, nbre);
		checkCond(taille != nbre, "writing failed");
	}
	fork_and_run(executerCat, fichier);
	
	close(file);

	fork_and_run(executerExec, fichier);
}