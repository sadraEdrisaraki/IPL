#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include "check.h"

typedef struct{
	char nom[64];
	char prenom[64];
	char sexe;
} record;

void checkCond(bool cond, char* msg) {
  if (cond) {
    perror(msg);
    exit(EXIT_FAILURE);
  }  
}

void checkNeg(int res, char* msg) {
  checkCond(res < 0, msg);
}

/* Main */	
int main(int argc, char **argv){
	
	int fd, i;
	record dt;
	int nbRec = 10;
	
	checkNeg((fd=open("data.bin", O_RDWR | O_CREAT | O_TRUNC, 0744)), "open failed.\n");
	checkNeg(write(fd, &nbRec, sizeof(int)), "write failed.\n");
	
	strcpy(dt.nom, "Rogne     "); strcpy(dt.prenom, "Yves   ") ; dt.sexe='H';
	checkNeg(write(fd, &dt, sizeof(record)), "write failed.\n");
	strcpy(dt.nom, "Dure      "); strcpy(dt.prenom, "Laure  ") ; dt.sexe='F';
	checkNeg(write(fd, &dt, sizeof(record)), "write failed.\n");
	strcpy(dt.nom, "Javel     "); strcpy(dt.prenom, "Aude   ") ; dt.sexe='F';
	checkNeg(write(fd, &dt, sizeof(record)), "write failed.\n");
	strcpy(dt.nom, "Coeur     "); strcpy(dt.prenom, "Marc   ") ; dt.sexe='H';
	checkNeg(write(fd, &dt, sizeof(record)), "write failed.\n");
	strcpy(dt.nom, "Faitmal   "); strcpy(dt.prenom, "Oussama") ; dt.sexe='H';
	checkNeg(write(fd, &dt, sizeof(record)), "write failed.\n");
	strcpy(dt.nom, "Tare      "); strcpy(dt.prenom, "Guy    ") ; dt.sexe='H';
	checkNeg(write(fd, &dt, sizeof(record)), "write failed.\n");
	strcpy(dt.nom, "Diotte    "); strcpy(dt.prenom, "Kelly  ") ; dt.sexe='F';
	checkNeg(write(fd, &dt, sizeof(record)), "write failed.\n");
	strcpy(dt.nom, "Deuf      "); strcpy(dt.prenom, "John   ") ; dt.sexe='H';
	checkNeg(write(fd, &dt, sizeof(record)), "write failed.\n");
	strcpy(dt.nom, "Assin     "); strcpy(dt.prenom, "Marc   ") ; dt.sexe='H';
	checkNeg(write(fd, &dt, sizeof(record)), "write failed.\n");
	strcpy(dt.nom, "Potenpoche"); strcpy(dt.prenom, "Jessica") ; dt.sexe='F';
	checkNeg(write(fd, &dt, sizeof(record)), "write failed.\n");
	
	checkNeg(lseek(fd, 0, SEEK_SET), "lseek failed.\n");
	
	checkNeg(read(fd, &nbRec, sizeof(int)), "read failed.\n");
	printf("%d enregistrements lus.\n", nbRec);
	
	for(i = 0; i < nbRec; i++){
		checkNeg(read(fd, &dt, sizeof(record)), "read failed.\n");
		printf("Nom : %s, Prénom : %s, sexe : %c\n", dt.nom, dt.prenom, dt.sexe);
	}
	
	checkNeg(close(fd), "close failed.\n");
}
