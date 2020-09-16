#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STRING_COUNT 6


int main(int argc, char *argv[])
{
	char *tabPtr[STRING_COUNT+1] =  {"Exercices", "de" , "langage", "C", "2eme", "bloc"};

	printf("Affichage 1er tableau : \n");
	for (int i = 0; i < STRING_COUNT; i++)
	{
		printf("%s\n", tabPtr[i]);
	}

	/*initialisation du tableau dynamique*/
	char **tabPtrCopy = NULL;

	tabPtrCopy = (char**) malloc((STRING_COUNT+1)*sizeof(char*));
	if (!tabPtrCopy)
	{
		perror("erreur d'allocation dynamique");
		exit(1);
	}

	for (int i = 0; i < STRING_COUNT; i++)
	{
		tabPtrCopy[i] = (char*) malloc(strlen(tabPtr[i]) * sizeof(char));
		if (!tabPtrCopy)
		{
			perror("erreur d'allocation dynamique");
			exit(1);
		}

		strcpy(tabPtrCopy[i], tabPtr[i]);
	}

	printf("Affichage 2eme tableau : \n");
	for (int i = 0; i < STRING_COUNT; i++)
	{
		printf("%s\n", tabPtrCopy[i]);
	}

	printf("Affichage spécial : \n");
	for (int i = 0; i < STRING_COUNT; i++) {

		for (int j = 0; j < strlen(tabPtr[i]); j++) {

			printf("%c\n",tabPtr[i][j]);
		}
	}

	//printf("%s\n", tabPtr[1][1]); // pq erreur de segmentation ???? 
	printf("%d\n", tabPtr);

	for (int i = 0; i < STRING_COUNT; i++) 
	{
		free(tabPtrCopy[i]);
	}

	free(tabPtrCopy);


	return 0;
}