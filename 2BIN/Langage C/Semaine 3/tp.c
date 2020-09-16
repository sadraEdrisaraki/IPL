#include <stdlib.h>
#include <stdio.h>
#include<stdbool.h>


char** initialisation (int hauteur, int largeur, char** puissance)
{
	puissance = (char**) malloc(hauteur * sizeof(char*));

	
	for (int i = 0; i < hauteur; i++) 
	{
		puissance[i] = (char*) malloc(largeur*sizeof(char));
	}


	//remplissage de '.' dans le tableau
	for (int i = 0; i < hauteur; i++) 
	{
		for (int j = 0; j < largeur; j++) 
		{
			puissance[i][j] = '.';
		}
	}

	return puissance;
}



void affichage (int hauteur, int largeur, char** puissance) 
{

	for (int i = 0; i < hauteur; i++) 
	{

		for (int j = 0; j < largeur; j++) 
		{
			printf("%c\t",puissance[i][j] );
		}

		printf("\n");
	}
}


int main(){

	int hauteur;
	int largeur;
	int indexNumCol;
	char **puissance;

	printf("Bienvenue dans le jeu Puissance4\n");
	printf("Entrer la hauteur du tableau : \n");
	scanf("%d",&hauteur);
	printf("Entrez la largeur du tableau : \n");
	scanf("%d",&largeur);
	

	puissance = initialisation(hauteur, largeur, puissance);
	affichage(hauteur, largeur, puissance);



	while(1) 
	{
		printf("colonne du joueur de X ? : \n");
		scanf("%d",&indexNumCol);



		// agrandir : si l'index est plus grand que celui de base alors on agrandi 
		if (indexNumCol > largeur)
		{
			//realloc 
			largeur = indexNumCol;

			for (int i = 0; i < hauteur; i++ ) 
			{
				puissance[i] = realloc(puissance[i], largeur * sizeof(char)); 
			}

			//remplissage de '.' dans le tableau
			for (int i = 0; i < hauteur; i++) 
			{
				for (int j = 0; j < largeur; j++) 
				{
					puissance[i][j] = '.';
				}
			}

			affichage(hauteur, largeur, puissance);

		} 





		indexNumCol--; // si il entre 1 ça correspond à l'index 0

		// le joueur place dans la colonne, savoir dans quelle ligne mettre
		for (int i = 0; i < hauteur; i++) 
		{
			//commencer par le dernier indice
			int indexNumLig = hauteur - i - 1;

			if ( puissance[0][indexNumCol] == '.') 
			{
				if ( puissance[indexNumLig][indexNumCol] == '.') 
				{
					puissance[indexNumLig][indexNumCol] = 'X';
					break;
				} 
			}
		}


		printf("colonne du joueur de O ? : \n");
		scanf("%d",&indexNumCol);
		indexNumCol--; // si il entre 1 ça correspond à l'index 0

		// le joueur place dans la colonne, savoir dans quelle ligne mettre
		for (int i = 0; i < hauteur; i++) 
		{
			//commencer par le dernier indice
			int indexNumLig = hauteur - i - 1;

			if ( puissance[0][indexNumCol] == '.') 
			{
				if ( puissance[indexNumLig][indexNumCol] == '.') 
				{
					puissance[indexNumLig][indexNumCol] = '0';
					break;
				} 
			}
		}



		affichage(hauteur, largeur, puissance);

	}


	// libere la memoire
	for (int i = 0; i < hauteur; i++) 
	{
		free(puissance[i]);
	}
	free(puissance);


}