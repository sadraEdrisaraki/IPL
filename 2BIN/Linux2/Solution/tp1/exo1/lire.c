#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 10

int main(int argc, char **argv){
	char buffer[MAX];
	//Le \n est inclus dans le read
	printf("Veuillez introduire votre ligne(max 10 caractères) : \n");
	int nbre = read(0, buffer, MAX);
	while(nbre>0){

		//Si + de 10 caractères
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

			//Message pour recommencer
			printf("Votre chaîne fait + de %d caractères. Veuillez réessayer.\n", MAX);
		
		//Si - de 10 caractères
		}else{

			//On va écrire la ligne en stdout
			if(write(1, buffer, nbre)!=nbre){
				perror("Error writing");
				exit(EXIT_FAILURE);
			}
			printf("Veuillez introduire votre ligne(max 10 caractères) : \n");
		}
		nbre = read(0, buffer, MAX);
	}
	if(nbre==-1){
		perror("Error reading");
		exit(EXIT_FAILURE);
	}
	return 0;
}