/// Compilation avec l'options:  -D_POSIX_C_SOURCE
/// (cf. man 7 feature_test_macros)

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include "check.h"
#include "fork.h"

// définition d’un gestionnaire de signal
void sigusr1_handler (int sig) {
   printf("[Processus %d] Signal handler: SIGUSR1 recu --> exit\n",
                getpid());  // cette fonction n'est pas async-signal-safe!
   exit(10);
}

// code du fils
void run(void *argv) {   
   /* PROCESSUS FILS */
   printf("[PID=%d] Je suis le fils\n", getpid());  // message non affiché si le scheduler
                                                    // passe la main au père après fork()

   // boucle infinie
   int i = 0;
   while (1) {
      i++;
   }

   exit(EXIT_SUCCESS);
}

int main () {
   int ret,statut;

   // armement d'un handler pour SIGUSR1
   printf("Armement du signal SIGUSR1\n");
   struct sigaction newact;
   newact.sa_handler = sigusr1_handler;
   int ret = sigemptyset(&newact.sa_mask);
   checkNeg(ret, "erreur sigemptyset");
   newact.sa_flags = 0;
   ret = sigaction(SIGUSR1, &newact, NULL);
   checkNeg(ret, "erreur sigaction 2");

   pid_t pid = fork_and_run(run, NULL);
      
   /* PROCESSUS PARENT */
   printf("Je suis le pere de PID %d - ", pid);
   printf("envoi du signal SIGUSR1 à mon fils\n");
   // envoi d'un signal SIGUSR1 au processus fils
   ret = kill(pid,SIGUSR1);
   checkNeg(ret, "erreur kill SIGUSR1");
   // attente de la mort du fils
   pid=swaitpid(pid,&statut,0);
   printf("Statut de mon fils %d: %d\n", pid, WEXITSTATUS(statut));
   
   exit(EXIT_SUCCESS);
}

/*
  OUPUT :

  Armement du signal SIGUSR1
  Je suis le pere de PID 8800 - envoi du signal SIGUSR1 à mon fils
  [Processus 8800] Signal handler: SIGUSR1 recu --> exit
  Statut de mon fils 8800: 10

*/
