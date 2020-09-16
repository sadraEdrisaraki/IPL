#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10

//*****************************************************************************
// CHECK
//*****************************************************************************

//PRE: msg != NULL
//POST: 1) If the value of "cond" is true, "msg" followed by a message 
//      describing the last error encountered during a call 
//      to a system or library function is produced 
//      on stderr. Moreover, the program is abruptly terminied.
//      2) If the value of  "cond" is false, nothing happens. 
void checkCond(bool cond, char* msg) {
  if (cond) {
    perror(msg);
    exit(EXIT_FAILURE);
  }  
}

//*****************************************************************************
// CLEAR STDIN
//*****************************************************************************

// POST: Read all the characters on stdin up and including a '\n'
//       Moreover, the program is abruptly terminated when an error occurs.
void clearStdin() {
  char c;
  int nbCharRd = read(0, &c, 1);
	while(nbCharRd == 1 && c != '\n') {
	  nbCharRd = read(0, &c, 1);
	}
	checkCond(nbCharRd == -1, "Error reading stdin");
}

//*****************************************************************************
// MAIN
//*****************************************************************************

int main(int argc, char **argv) {
	
	// An extra space for '\0' at the end of the string is not needed
	// or the reason that "string.h" is not used in this program.
	char bufRd[BUFFER_SIZE];
	
	printf("Introduisez votre ligne (max 10 caractères) : \n");
	
	int nbCharRd = read(0, bufRd, BUFFER_SIZE);
	while(nbCharRd > 0) { 
		if(bufRd[nbCharRd - 1] == '\n') { 
			int res = write(1, bufRd, nbCharRd);
			checkCond(res != nbCharRd, "error wrinting stdout");
			printf("Introduisez votre ligne (max 10 caractères) : \n");
		} else { 
		  clearStdin();
			printf("Ligne de plus de 10 caractères, recommencez svp\n");
		}
		nbCharRd = read(0, bufRd, BUFFER_SIZE);
	}

	checkCond(nbCharRd == -1, "Error reading stdin");
	return 0;
}