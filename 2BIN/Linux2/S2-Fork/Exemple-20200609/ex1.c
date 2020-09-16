#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//*****************************************************************************
// CHECK
//*****************************************************************************

//PRE: msg != NULL
//POST: 1) If the value of "cond" is false, "msg" followed by a message 
//      describing the last error encountered during a call 
//      to a system or library function is produced 
//      on stderr. Moreover, the program is abruptly terminied.
//      2) If the value of  "cond" is true, nothing happens. 
void checkCond(bool cond, char* msg) {
  if (cond) {
    perror(msg);
    exit(EXIT_FAILURE);
  }  
}


int main(int argc, char **argv) {
  /* pid de l’enfant */
  int childId = fork();
  checkCond(childId == -1, "Fork failed");

  if(childId != 0) {
    /* In the parent process */
    printf("Processus parent en attente de la fin de son enfant (pid fils=%i).\n",childId);

    /* Statut de l’enfant terminé */
    int status;
    /* pid renvoyé par le wait */
    int waitId = waitpid(childId, &status, 0);
    checkCond(waitId == -1, "Wait error");
    
    if(waitId != childId) {
      /* Impossible */
      printf("M'enfin, qui m'a fait un enfant dans le dos?!");
    } else {
      printf("Processus parent se termine après son enfant (pid fils=%i).\n",childId);
    }
  } else { 
    /* In the child process */
    printf("Je suis le fils '%s': pid=%i - ppid=%i\n",argv[0],getpid(),getppid());
    execl("myScript.sh","myScript.sh", NULL);
    checkCond(true, "Exec failed");
  }
}