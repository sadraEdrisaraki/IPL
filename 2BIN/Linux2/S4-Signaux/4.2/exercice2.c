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

#define SIG 15



// définition d’un gestionnaire de signal
void sigusr1_handler (int sig) {
   printf("[Processus %d] Signal handler: %s recu --> exit\n", getpid(), sys_siglist[sig]);  // cette fonction n'est pas async-signal-safe!
   
}

int main () {
   int ret;
	
      
   /* PROCESSUS */
  
   struct sigaction newact;
   newact.sa_handler = sigusr1_handler;

   // armement d'un handler pour tous les signaux
   for (int i = 0; i < SIG; ++i)
   {
     printf("[PID=%d] Armement du signal %s\n", getpid(), sys_siglist[i]);
     ret = sigaction(i, &newact, NULL); // arme un handler pour le signal
     if (ret == -1){
      perror("non capturé");
     }
   }

   // boucle infinie
   while (true) {
      read(0,NULL, sizeof(int));
   }

   exit(EXIT_SUCCESS);
}

/*
  OUPUT :

  Blocage des signaux SIGUSR1
  Je suis le pere de PID 3873 - envoi du signal SIGUSR1 à mon fils
  [PID=3873] Je suis le fils
  [PID=3873] Armement du signal SIGUSR1
  [PID=3873] Déblocage du signal SIGUSR1
  [Processus 3873] Signal handler: SIGUSR1 recu --> exit
  Statut de mon fils 3873: 10

*/