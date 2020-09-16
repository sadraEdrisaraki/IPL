#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/wait.h>
#include <string.h>
#include "check.h"

#define NOM_FICHIER_OUT "resultat.bin" /* Nom du fichier resultat */

typedef struct { /* structure des enregistrements */
	char nom[64];
	char prenom[64];
	char sexe;
} record;

void maj(char *chaine){ /* Mise en majuscules */
	int i=0;
	while(chaine[i]!='\0'){
		chaine[i] = toupper(chaine[i]);
		i++;
	}
}

int main(int argc, char **argv){
	
	int fd, child_pid, i;
	int nbRecords; /* Nb d'enregistrements */
	
	/* A COMPLETER : inclure ici les instructions d'ouverture du fichier "resultat" :
		en lecture et ecriture + vider le fichier + creer le fichier si necessaire,
		de création du pipe et de création du processus fils */
	fd = open(NOM_FICHIER_OUT, O_CREAT | O_TRUNC | O_RDWR, 0666); //permissions à effet uniquement quand le fichier est créer.
	checkNeg(fd, "open resultat.bin failed");
	
	int pipefd[2];
	int res = pipe(pipefd);
	checkNeg(res, "error pipe");
	child_pid = fork();
	checkNeg(child_pid, "error fork");
	
	
	
	if(child_pid){ /* Processus pere */
		int nb_h = 0; /* Pour comptage enregistrements avec sexe = 'H' */
		char rec_formate[256]; /* Pour affichage lors de la lecture finale */
		record *rec; /* Pour lecture d'un enregistrement */
		record **tab_rec; /* Pour stockage des enregistrements dans un tableau */
		
		/* A COMPLETER */
		res = close(pipefd[0]);
		checkNeg(res, "error close père");
		
		tab_rec = malloc(sizeof(record*)); /* Allocation memoire */
		checkNull(tab_rec, "malloc\n");
	
		/* Traitement des enregistrements */
		/* Lecture de l'int indiquant le nb d'enregistrements : A COMPLETER */
		
		res = read(0, &nbRecords, sizeof(int));
		checkNeg(res, "error read nbRecords");
		
		for(i = 0; i < nbRecords; i++){
			rec = malloc(sizeof(record)); /* Allocation memoire enregistrement suivant */
			checkNull(rec, "malloc\n");
			/* Lecture d'un enregistrements : A COMPLETER */
			res = read(0, rec, sizeof(*rec));
			checkNeg(res, "error read enregistrement "+i);
			
			if(rec->sexe == 'H'){
				nb_h++;
				maj((char *)&(rec->nom));
				tab_rec = realloc(tab_rec, nb_h*sizeof(record*));
				checkNull(tab_rec, "realloc\n");
				*(tab_rec+nb_h-1) = rec;	
			} else {
				/* Communiquer l'information au fils : A COMPLETER */
				res = write(pipefd[1], rec, sizeof(*rec));
				free(rec); /* Liberation memoire non utilisee */
			}			
		}
		/* A COMPLETER */
		res = close(pipefd[1]);
		checkNeg(res, "error close père");
		
		
		printf("Moi, le pere, j'ai traite %d enregistrements de sexe = 'H'\n", nb_h);
		/* Attente de la fin du fils : A COMPLETER */
		pid_t wait = waitpid(child_pid, NULL, 0);
		checkNeg(wait, "error wait");
		
		/* Ecriture des info dans le fichier resultat, d'abord le nb d'enregistrements traites par le pere,
			puis chacun des enregistrements : A COMPLETER */

		res = write(fd, &nb_h, sizeof(int));
		checkNeg(res, "error write");
		for(int i = 0; i<nb_h; i++){
			res = write(fd, tab_rec[i], sizeof(*(tab_rec[i])));
			checkNeg(res, "error write");
			free(tab_rec[i]);
		}
		free(tab_rec);
		
		/* Lecture des info dans le fichier resultat et ecriture sur la sortie standard */
		checkNeg(lseek(fd, 0, SEEK_SET), "lseek failed.\n");
		rec = malloc(sizeof(record)); /* Allocation memoire */
		checkNull(rec, "malloc\n");
		checkNeg(read(fd, &nbRecords, sizeof(int)), "read failed.\n");
		for(i = 0; i < nbRecords; i++) { /* Sexe = 'F' */
			checkNeg(read(fd, rec, sizeof(record)), "read failed.\n");
			sprintf(rec_formate, "Nom : %s\tPrenom : %s\tSexe : %c\n", rec->nom, rec->prenom, rec->sexe);
			checkNeg(write(1, rec_formate, strlen(rec_formate)), "write failed.\n");			
		}
		checkNeg(read(fd, &nbRecords, sizeof(int)), "read failed.\n");
		for(i = 0; i < nbRecords; i++) { /* Sexe = 'H' */
			checkNeg(read(fd, rec, sizeof(record)), "read failed.\n");
			sprintf(rec_formate, "Nom : %s\tPrenom : %s\tSexe : %c\n", rec->nom, rec->prenom, rec->sexe);
			checkNeg(write(1, rec_formate, strlen(rec_formate)), "write failed.\n");			
		}
		
		exit(EXIT_SUCCESS);

	} else { /* Processus fils */
		int lecture; /* nb octets lus */
		int nb_f = 0; /* Pour comptage enregistrements avec sexe = 'F' */
		record *rec; /* Pour lecture d'un enregistrement */
		record **tab_rec; /* Pour stockage des enregistrements dans un tableau */

		/* A COMPLETER */
		int res;
		res = close(pipefd[1]);
		checkNeg(res, "error close");
		
		
		/* Allocation memoire */		
		rec = malloc(sizeof(record));
		checkNull(rec, "malloc\n");

		tab_rec = malloc(sizeof(record*));
		checkNull(tab_rec, "malloc\n");

		/* Traitement des enregistrements recus du pere */
		while((lecture = read(pipefd[0], rec, sizeof(*rec)))){
			checkNeg(lecture, "read failed.\n");
			nb_f++;
			maj((char *)&(rec->nom));
			tab_rec = realloc(tab_rec, nb_f*sizeof(record*));
			checkNull(tab_rec, "realloc\n");
			
			*(tab_rec+nb_f-1) = rec;
			rec = malloc(sizeof(record)); /* Allocation memoire enregistrement suivant */
		    checkNull(rec, "malloc\n");
		}

		free(rec); /* Liberation memoire non utilisee */
		
		/* A COMPLETER */
		lecture = close(pipefd[0]);
		checkNeg(lecture, "error lecture");
		
		
		printf("Moi, le fils, j'ai traite %d enregistrements de sexe = 'F'\n", nb_f);
		
		/* Ecriture des info dans le fichier resultat, d'abord le nb d'enregistrements traites par le fils,
			puis chacun des enregistrements : A COMPLETER */
		
		res = write(fd, &nb_f, sizeof(int));
		checkNeg(res, "error write");
		for(int i = 0; i<nb_f; i++){
			res = write(fd, tab_rec[i], sizeof(*(tab_rec[i])));
			checkNeg(res, "error write");
			free(tab_rec[i]);
		}
		free(tab_rec);
			
			
		exit(EXIT_SUCCESS);
	}	
}
