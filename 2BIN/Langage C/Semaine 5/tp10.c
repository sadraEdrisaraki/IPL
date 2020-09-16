#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INIT_SIZE_TAB 10
#define ID_SIZE 5
#define MAX_CHAR 256

int main(int argc, char *argv[])
{
	

	char **tab;

	int phys_size = 5;
	int logique_size = 0;

	char ligne[MAX_CHAR]; // tableau de char, utilise pour la lecture


	// init le tableau 
   	tab = (char**) malloc(phys_size*sizeof(char*));

   	/*
	for (int i = 0; i < phys_size; ++i)
	{
		tab[i] = (char*) malloc(MAX_CHAR*sizeof(char));
	}
	*/


	// lit sur la console
	while (fgets(ligne, MAX_CHAR, stdin) != NULL) 
	{
		// !! attention au \n 
		int word_size = strlen(ligne) - 1;
		printf("%s\n", ligne);
		printf("%d\n", strlen(ligne));
		printf("%d\n", logique_size);
		bool inside = false; 

		
		for (int i = 0; i < logique_size; i++) 
		{
			if (strncmp(ligne, tab[i], ID_SIZE))
			{
				printf("%s\n", "correspond");
			}
		}

		// realloc
		if (logique_size == phys_size) 
		{
			tab = (char**) realloc(tab, phys_size * 2);
		}

		tab[logique_size] = (char*) malloc(word_size*sizeof(char));
		tab[logique_size] = ligne;


		//affichage

		for (int i = 0; i < phys_size; i++) 
		{
			if (tab[i] != NULL) 
			{
				printf("%s\n", tab[i]);
			}
		}


		logique_size++;
	

	}






















	/*

	while(fgets(,, stdin) )
	{
	text = realloc( text, strlen(text)+1+strlen(buffer) );
	if( !text ) ...
	strcat( text, buffer ); 
	printf("%s\n", buffer);
	}

	char **dest;

	**dest = (char**) malloc(7*sizeof(char*));

	for (int i = 0; i < argc; i++) 
	{
		printf("%s\n", argv[i]);
	}
	*/

	//for (int i = 0; i < ; i++) 
	//{
		//dest[i] = (char*) malloc(strlen(tabPtr[i]) * sizeof(char));

	//}


	return 0;
}