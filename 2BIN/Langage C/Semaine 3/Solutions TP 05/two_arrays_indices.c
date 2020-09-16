#include <stdio.h>
#include <stdlib.h>

// SOLUTION PAR INDICES
// Cette solution suppose que l'utilisateur ne fera pas d'erreur 
// en introduisant les données

// Liens vers vidéo explicative: https://youtu.be/3se3fusg7zc

int main (int argc, char **argv)
{
   int nbrData, nbrPositives, nbrNegatives;
   int *inputs, *positives, *negatives;

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
      for (int i=0; i<nbrData; i++) {
         scanf("%d", inputs+i);
         if (inputs[i]>=0)
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
      nbrPositives = nbrNegatives = 0;
      for (int i=0; i<nbrData; i++) {
         if (inputs[i]>=0) {
            positives[nbrPositives] = inputs[i];
            nbrPositives++;
         }
         else {
            negatives[nbrNegatives] = inputs[i];
            nbrNegatives++;
         }
      }

      // Print arrays
      printf("Resultat : \n");
      for (int i=0; i<nbrPositives; i++)
         printf("%d ", positives[i]);
      printf("\n");

      for (int i=0; i<nbrNegatives; i++)
         printf("%d ", negatives[i]);
      printf("\n");

      // Free dynamic memory
      free(inputs);
      free(negatives);
      free(positives);

      printf("Entrez le nombre de donnees (0 pour terminer): ");
      scanf("%d", &nbrData);
   }
        
   exit(EXIT_SUCCESS);
}
