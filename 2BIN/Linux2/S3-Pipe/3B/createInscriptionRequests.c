#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "InscriptionRequest.h" 


int main()
{
	FILE * file;
	file = fopen("DemandesInscriptions.bin","wb");
	
	InscriptionRequest ir1;
	strcpy(ir1.name,"DRATHEY");
	strcpy(ir1.firstname,"Daisy");
	ir1.nbYearPastInEducation = 3;
	
	fwrite(&ir1,sizeof(ir1),1,file);
	printf("la taille d'un enregistrement de structure vaut donc : %zu\n", sizeof(ir1));	
	
	InscriptionRequest ir2;
	strcpy(ir2.name,"OCHON");
	strcpy(ir2.firstname,"Paul");
	ir2.nbYearPastInEducation = 2;
	
	fwrite(&ir2,sizeof(ir2),1,file);
	printf("la taille d'un enregistrement de structure vaut donc : %zu\n", sizeof(ir2));	

	InscriptionRequest ir3;
	strcpy(ir3.name, "UZI");
	strcpy(ir3.firstname,"Jack");
	ir3.nbYearPastInEducation =1;
	
	fwrite(&ir3,sizeof(ir3),1,file);
	printf("la taille d'un enregistrement de structure vaut donc : %zu\n", sizeof(ir3));
    
    fclose(file);
    return 0;
}	
