#include <stdio.h>
#include <stdlib.h>

#include "gen.h"
#include "utils.h"

#define MAX_X  10
#define MAX_Y  10
#define READ_SIZE 2


void verificationPosition(int * coordonnees) {
	
	if (coordonnees[1] == MAX_Y) {
		coordonnees[1] = 0;
	} else if (coordonnees[1] == -1) {
		coordonnees[1] = 9;
	}

	if (coordonnees[0] == MAX_X) {
		coordonnees[0] = 0;
	} else if (coordonnees[0] == -1) {
		coordonnees[0] = 9;
	}

}
//******************************************************************************
// MAIN FUNCTION
//******************************************************************************
int main (int argc, char *argv[]) {

	int shm_id;
	int *coordonnees = init_shm(SHM_KEY, 0, 0, &shm_id); // récupère la mémoire partagée 

	int sem_id = ssemget(SEM_KEY, 0, 0);


	swrite(1, ">>>", 3);
	printf("X = %d , Y = %d\n",coordonnees[0],coordonnees[1]);
	char buff[READ_SIZE];
	int res = sread(0, buff, READ_SIZE);
	while(buff[0] != 'Q' && res != 0) { 
		sdown(sem_id, 0);
		switch(buff[0]) {
			case 'U'://Nord
				coordonnees[1]++;
				break;
			case 'D': //Sud
				coordonnees[1]--;
				break;
			case 'L': //Ouest
				coordonnees[0]--;
				break;
			case 'R': //Est
				coordonnees[0]++;
				break;
		}

		verificationPosition(coordonnees);
		swrite(1, ">>>", 3);
		printf("X = %d , Y = %d\n",coordonnees[0],coordonnees[1]);
		sup(sem_id, 0);
		res = sread(0, buff, READ_SIZE);
	}

	sshmdt(coordonnees);
	exit(0);
}