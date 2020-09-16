// ex4.1.c - compiler avec une option: -D_POSIX_C_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include "check.h"
#include "fork.h"

int compt = 7;

void sighandler () {
   printf("--> Signal SIGUSR1 reçu! ");
   compt--;
}

// CODE DU PROCESSUS FILS
void run(void *argv) {
   // armement du handler de signal SIGUSR1
   struct sigaction newact;
   newact.sa_handler = sighandler;
   int ret = sigemptyset(&newact.sa_mask);
   checkNeg(ret, "erreur sigemptyset");
   newact.sa_flags = 0;
   ret = sigaction(SIGUSR1, &newact, NULL);
   checkNeg(ret, "erreur sigaction");
   
   // le fils attend un signal
   printf("OK il me reste %d vies\n",compt);
   int precVal = compt;
   while (compt != 0) {
      if (compt != precVal) {
         printf("OK il me reste %d vies\n",compt);
      	 precVal = compt;
      }
   }
   printf("That's all, folks!\nFin du fils\n");
   exit(EXIT_SUCCESS);
}


int main () {
   int res;
   pid_t pid = fork_and_run(run, NULL);

   // PROCESSUS PARENT
   for (int i=0; i<7; i++) {
      sleep(1);
      printf("Le pere envoie le signal SIGUSR1 a son fils\n") ;
      res = kill(pid,SIGUSR1);
      checkNeg(res, "syscall error: kill SIGUSR1");
   }
   swaitpid(pid, NULL, 0);
   printf("Fin du pere\n");
}
