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
   printf("[PID=%d] Je suis le fils\n", getpid());

   // armement d'un handler pour SIGUSR1
   printf("[PID=%d] Armement du signal SIGUSR1\n", getpid());
   struct sigaction newact;
   newact.sa_handler = sigusr1_handler;
   int ret = sigemptyset(&newact.sa_mask);
   checkNeg(ret, "erreur sigemptyset");
   newact.sa_flags = 0;
   ret = sigaction(SIGUSR1, &newact, NULL);
   checkNeg(ret, "erreur sigaction");

   // déblocage du signal SIGUSR1
   printf("[PID=%d] Déblocage du signal SIGUSR1\n", getpid());
   sigset_t unblock;
   ret = sigemptyset(&unblock);
   checkNeg(ret, "sigemptyset");
   ret = sigaddset(&unblock, SIGUSR1);
   checkNeg(ret,"sigaddset on unblock");
   ret = sigprocmask(SIG_UNBLOCK, &unblock, NULL);
   checkNeg(ret, "sigprocmask: SIG_UNBLOCK"); 

   // boucle infinie
   int i = 0;
   while (1) {
      i++;
   }

   exit(EXIT_SUCCESS);
}

int main () {
   int ret,statut;

   // blocage des signaux SIGUSR1 pour s'assurer
   // qu'un signal SIGUSR1 ne sera pas 'manqué' par le fils
   printf("Blocage des signaux SIGUSR1\n");
   sigset_t blocked;
   ret = sigemptyset(&blocked);
   checkNeg(ret,"sigemptyset on blocked");
   ret = sigaddset(&blocked, SIGUSR1);
   checkNeg(ret,"sigaddset on blocked");
   ret = sigprocmask(SIG_BLOCK, &blocked, NULL);
   checkNeg(ret,"sigprocmask: SIG_BLOCK");
	
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

  Blocage des signaux SIGUSR1
  Je suis le pere de PID 3873 - envoi du signal SIGUSR1 à mon fils
  [PID=3873] Je suis le fils
  [PID=3873] Armement du signal SIGUSR1
  [PID=3873] Déblocage du signal SIGUSR1
  [Processus 3873] Signal handler: SIGUSR1 recu --> exit
  Statut de mon fils 3873: 10

*/
