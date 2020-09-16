#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX 80

int main(int argc, char **argv){
	if (argc != 3){
		printf("Usage : argv[0] file1 file2\n");
		exit(0);
	}
	int fd1 = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0660);
	if(fd1 == -1){
		perror("Error open file1");
		exit(EXIT_FAILURE);
	}
	int fd2 = open(argv[2], O_CREAT|O_TRUNC|O_WRONLY, 0660);
	if(fd2 == -1){
		perror("Error open file2");
		exit(EXIT_FAILURE);
	}

	char buffer[MAX];

	int nbre = read(0, buffer, MAX);
	while(nbre>0){
		//Si + de 80 caractères
		if(buffer[nbre-1] != '\n'){

			//On va clean le stdin
			char c;
			int nbrChar = read(0, &c, 1);
			while(nbrChar == 1 && c != '\n'){
				nbrChar = read(0, &c, 1);
			}
			if(nbrChar == -1){
				perror("Error reading");
				exit(EXIT_FAILURE);
			}
		
		//Si - de 80 caractères
		}else{
			//Si ça commence avec lettre maj
			if(buffer[0] >= 'A' && buffer[0] <= 'Z'){
				//On va écrire la ligne en stdout
				if(write(fd1, buffer, nbre)!=nbre){
					perror("Error writing");
					exit(EXIT_FAILURE);
				}
			//Si ça commence avec lettre min	
			}else if(buffer[0] >= 'a' && buffer[0] <= 'z'){
				if(write(fd2, buffer, nbre)!=nbre){
					perror("Error writing");
					exit(EXIT_FAILURE);
				}
			}
			
		}
		nbre = read(0, buffer, MAX);
	}
	if(nbre==-1){
		perror("Error reading");
		exit(EXIT_FAILURE);
	}
	close(fd1);
	close(fd2);
	return 0;
}
