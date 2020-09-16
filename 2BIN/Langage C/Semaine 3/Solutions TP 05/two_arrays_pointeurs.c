#include <stdio.h>
#include <stdlib.h>

// SOLUTION PAR POINTEURS
// Cette solution suppose que l'utilisateur ne fera pas d'erreur 
// en introduisant les données

// Lien vers viédo explicative: https://youtu.be/O6y44pPcHHA

int main (int argc, char **argv)
{
   int nbrData, nbrPositives, nbrNegatives;
   int *inputs, *positives, *negatives;;

   printf("Entrez le nombre de donnees (0 pour terminer): ");
   scanf("%d", &nbrData);

   while (nbrData>0) {
      inputs = malloc(nbrData*sizeof(int));
      if (inputs == NULL) {
         perror("Out of memory\n");
         exit(EXIT_FAILURE);
      }

      // Read inputs and counts neg and pos
      printf("Entrez les donnees:\n");        
      nbrPositives = nbrNegatives = 0;
      for (int* ptr = inputs; ptr-inputs<nbrData; ptr++) {
         scanf("%d", ptr);
         if (*ptr>=0)
            nbrPositives++;
         else
            nbrNegatives++;
      }

      positives = malloc(nbrPositives*sizeof(int));
      if (positives == NULL) {
         perror("Out of memory\n");
         exit(EXIT_FAILURE);
      }
      negatives = malloc(nbrNegatives*sizeof(int));
      if (negatives == NULL) {
         perror("Out of memory\n");
         exit(EXIT_FAILURE);
      }

      // Fill pos and neg arrays        
      int* ptrP = positives;
      int* ptrN = negatives;
      for (int* ptr = inputs; ptr-inputs<nbrData; ptr++) {
         if (*ptr>=0) {
            *ptrP = *ptr;
            ptrP++;
         }
         else {
            *ptrN = *ptr;
            ptrN++;
         }
      }

      // Print arrays
      printf("Resultat : \n");
      for (int* ptrP = positives; ptrP-positives<nbrPositives; ptrP++)
         printf("%d ", *ptrP);
      printf("\n");

      for (int* ptrN = negatives; ptrN-negatives<nbrNegatives; ptrN++)
         printf("%d ", *ptrN);
      printf("\n");

      // Free dynamic memory
      free(inputs);
      free(negatives);
      free(positives);
		
      printf("Entrez le nombre de donnees: ");
      scanf("%d", &nbrData);
   }

   exit(EXIT_SUCCESS);
}
