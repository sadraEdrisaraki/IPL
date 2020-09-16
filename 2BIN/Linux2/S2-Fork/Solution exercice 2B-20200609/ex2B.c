#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>

#include "fork.h"

void child_handler(void *argv) {
  printf("4 5 6\n"); 
  exit(123);
}

int main (int argc, char *argv[]) {
  pid_t pid = fork_and_run(child_handler, NULL);
  
  int status;
  int waitres = swaitpid(pid, &status, 0); // Appel bloquant: attend l'enfant qu'il se termine
  // status contient le statut de comment c'est terminé l'enfant
  
  printf("1 2 3\n");
  
  if (waitres != pid) {
    dprintf(1, "This should not happen");
    exit(EXIT_FAILURE);
  }
  
  printf("Exit status of my child: %d\n", WEXITSTATUS(status));
  return 0;
}