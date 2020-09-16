#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 29

//PAS FINI BONUS 3 

int main(int argc, char *argv[]){

	char** tab;
	char ligne[MAX];
	int motPasPresent;
	int taille = argc-1;

	tab = (char**)malloc(taille*sizeof(char*));
	for (int i = 0; i < taille; ++i)
	{
		tab[i] = (char*)malloc(strlen(argv[i])*sizeof(char));
	}

	int indice;
	int presentDeuxFois;
	for (int i = 1; i < taille; ++i)
	{
		for (int j = 0; j < taille; ++j)
		{
			int cmp = strcmp(tab[j], argv[i]);
        	if(cmp==0){
        		presentDeuxFois = 1;
        		break;
        	}
		}
		if(presentDeuxFois!=1){
			strcpy(tab[indice], argv[i]);
			indice++;
		}

	}
    printf("Paramètres : \n");
	for (int i = 0; i < taille; ++i)
	{
		printf("%s\n", tab[i]);
	}
	printf("Entrez un mot\n");
    while (fgets(ligne, MAX, stdin) != NULL) {
    	int present = 0;

        for(int i=0; i<strlen(ligne); ++i){
            if(ligne[i]=='\n' || ligne[i]==' '){
                ligne[i]='\0';
            }
        }
    	int n = strlen(ligne);
    


        for (int i = 0; i < taille; ++i)
        {
        	int compare = strcmp(ligne, tab[i]);
        	if(compare==0){
        		present = 1;
        		break;
        	}

        }
        if(present==1){
        	printf("%s de longueur %d : present\n",ligne, n);
        }
        else{
        	motPasPresent++;
        	printf("%s de longueur %d : absent\n",ligne, n);
        }
        

        printf("Entrez un mot\n");
    }
    printf("Le nombre de fois qu'un mot n'as pas été trouvé dans la table : %d\n", motPasPresent);

    
}

