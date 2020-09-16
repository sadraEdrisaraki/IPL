#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>

#define MAX_SIZE 29

int main(int argc, char *argv[])
{
	int tailleDeTab = argc - 1;
	char **tableDeChar = NULL; // toujours init à NULL
	char ligne[MAX_SIZE];
	bool sameWord = false;
	int indice = 0; // A quelle indice copié dans le tableau 
	int motPasPresent = 0;

	// Allocation de la mémoire
	tableDeChar = (char**) malloc(tailleDeTab*sizeof(char*));
	if (!tableDeChar)
	{
		perror("erreur d'allocation de mémoire");
		exit(1);
	}

	for (int i = 0; i < tailleDeTab; i++)
	{
		tableDeChar[i] = (char*) malloc(strlen(argv[i]) *sizeof(char));
		if (!tableDeChar[i])
		{
			perror("erreur d'allocation de mémoire");
			exit(1);
		}
	}

	// parcours le tableau ARGV et mon tableau 
	// commence à 1 pour pas prendre le nom du programme.
	for (int i = 1; i < argc; i++)
	{
		for (int j = 0; j < tailleDeTab; j++)
		{
			if (strcmp(argv[i], tableDeChar[j]) == 0)
			{
				sameWord = true;
				break;
			}
		}

		// ne pas copié 2 fois le même mots
		if (!sameWord)
		{
			strcpy(tableDeChar[indice], argv[i]);
			indice += 1;

		}

		sameWord = false;
	}


	for (int i = 0; i < tailleDeTab; i++)
	{
		printf("%s\n", tableDeChar[i]);
	}


	while (fgets(ligne, MAX_SIZE, stdin) != NULL) 
	{
		bool present = false;

		// remplace le \n par le \o
		for(int i = 0 ; i < strlen(ligne); i++) 
		{
			if (ligne[i] == '\n' || ligne[i] == ' ')
			{
				ligne[i] = '\0';
			}
		}

		// Affichage
		printf("%s de longueur %d \n",ligne, (int) strlen(ligne));

		for(int i = 0 ; i < tailleDeTab; i++) 
		{
			if (strcasecmp(tableDeChar[i], ligne) == 0)
			{
				present = true;
				break;
			}
		}

		if (present) 
		{
			printf("Le mot : %s est présent dans le tableau.\n", ligne);
		}
		else
		{	
			motPasPresent += 1;
			printf("Le mot : %s n'est présent dans le tableau.\n", ligne);
		}

		/*
		for(int i = 0 ; i < strlen(ligne); i++) 
		{
			printf("lettre:%c,code ASCII : %d\n", ligne[i], ligne[i]);
		}
		*/

	}

	printf("Le nombre de fois qu'un mot n'as pas été trouvé dans la table : %d\n", motPasPresent);

	// Liberation de la mémoire
	for (int i = 0; i < tailleDeTab; i++)
	{
		free(tableDeChar[i]);
	}

	free(tableDeChar);



	return 0;
}