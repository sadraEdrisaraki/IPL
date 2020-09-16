#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void imprimerTable(char*, int*, int);
bool ajouterTable(int**, int*, int*, int);
int chargerTable(char**, int, int**, int*);

int main(int argc, char *argv[])
{	
	int tailleLogique = 0;
	int taillePhysique = 0;
	int* tab = NULL;
	char* legende = "Hello World !";
	int entier;

	tailleLogique = chargerTable(argv, argc, &tab, &taillePhysique);
	imprimerTable(legende, tab, tailleLogique);

	return 0;
}


void imprimerTable(char* legende, int* tab, int sz) 
{
	printf("%s\n", legende);
	for (int i = 0; i < sz; i++) 
	{
		printf("%d\n", tab[i]);
	}
}

bool ajouterTable(int** tab, int* tailleL, int* tailleP, int entier) 
{
	// tab non alloué, on l'alloue
	if (*tailleP == 0) 
	{
		*tailleP = 3;
		if ((*tab = (int*) malloc(*tailleP*sizeof(int))) == NULL) 
		{
			perror("Allocation dynamique impossible");
			return false;
		}
	}

	// saturation 
	if (*tailleL == *tailleP) 
	{
		*tailleP *= 2;
		if((*tab = (int*)realloc(*tab, *tailleP)) == NULL) 
		{
			perror("Allocation dynamique impossible");
			return false;
		}
	}

	(*tab)[*tailleL] = entier;
	*tailleL += 1;

	return true;
}

int chargerTable(char** mots, int nbrMots, int** tab, int* tailleP) 
{
	int entier;
	int tailleL; 

	for (int i = 1; i < nbrMots; i++) 
	{
		tailleL = i-1;
		entier = atoi(mots[i]);

		//printf("%d\n", entier);
		ajouterTable(tab, &tailleL, tailleP, entier);
	}

	return tailleL;
}