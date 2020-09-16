#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


#define MAX 80

int main(int argc, char **argv){
	if(argc != 3){
		printf("Usage : %s fichier1 fichier2\n", argv[0]);
		exit(0);
	}

	int file1 = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0660);
	if(file1 == -1){
		perror("Error open file1");
		exit(EXIT_FAILURE);
	}

	int file2 = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0660);
	if(file2 == -1){
		perror("Error open file2");
		exit(EXIT_FAILURE);
	}

	char phrase[MAX];
	

	while(fgets(phrase, MAX, stdin) != NULL){
		int nbre = strlen(phrase);
		if(phrase[nbre-1]!='\n'){
			char c;
			int nbreChar = read(0, &c, 1);
			while(nbreChar==1 && c != '\n'){
				nbreChar = read(0, &c, 1);
			}
			if(nbreChar == -1){
				perror("Error reading");
				exit(EXIT_FAILURE);
			}
		}
		char premiereLettre = phrase[0];
		if(premiereLettre>='A' && premiereLettre<='Z'){
			if(write(file1, phrase, nbre)!=nbre){
				perror("Error writing");
				exit(EXIT_FAILURE);
			}
		}
		if(premiereLettre>='a' && premiereLettre<='z'){
			if(write(file2, phrase, nbre)!=nbre){
				perror("Error writing");
				exit(EXIT_FAILURE);
			}
		}
	}
}