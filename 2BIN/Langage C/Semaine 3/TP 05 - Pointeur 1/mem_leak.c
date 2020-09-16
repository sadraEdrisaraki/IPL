#include <stdio.h>
#include <stdlib.h>

#define BLOC_SIZE 10000

//
// Programme démontrant une fuite mémoire ('memory leak').
//
int main (int argc, char **argv)
{
    int *t;
    while (1)
    {
        t = (int*) malloc(BLOC_SIZE * sizeof(double));
        
        if (t == NULL)
        {
            perror("Out of memory!\n");
            exit(1);
        }
        
        // Traitement hyptothétique sur le tableau
        // ...
        // Fin traitement
    }
}