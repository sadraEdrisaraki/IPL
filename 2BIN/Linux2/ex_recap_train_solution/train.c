#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

#include "check.h"

sig_atomic_t sig;


//*****************************************************************************
// HELPER FUNCTIONS
//*****************************************************************************

int sread(int fd, void* buff, int size) {
   int r = read(fd, buff, size);
   checkNeg(r, "Error READ");
   return r;
}

pid_t fork_and_run(void (*handler)()) {
   int childId = fork();
   checkNeg(childId, "Error [fork_and_run]");
  
   // child process
   if (childId == 0) {  
      (*handler)();
      exit(EXIT_SUCCESS);
   }
  
   return childId;
}

void swaitpid(pid_t pid, int* status) {
   pid_t waitId = waitpid(pid, status, 0);
   checkNeg(waitId, "Error waitpid()");
}

void ssigemptyset(sigset_t *set) {
  int res = sigemptyset(set);
  checkNeg(res, "sigemptyset");
}

void ssigfillset(sigset_t *set) {
  int res = sigfillset(set);
  checkNeg(res, "sigfillset");
}

void ssigaddset(sigset_t *set, int signum) {
  int res = sigaddset(set, signum);
  checkNeg(res, "sigaddset");
}

void ssigdelset(sigset_t *set, int signum) {
  int res = sigdelset(set, signum);
  checkNeg(res, "sigdelset");
}

void ssigaction(int signum, void (*handler)(int signum)) {
  struct sigaction action;
  action.sa_handler = handler;
  ssigfillset(&action.sa_mask);
  action.sa_flags = 0;
  
  int r = sigaction (signum, &action, NULL);
  checkNeg(r, "Error sigaction");
}

void ssigprocmask(int how, const sigset_t *set, sigset_t *oldset) {
  int res = sigprocmask(how, set, oldset);
  checkNeg(res, "sigprocmask");
}

void skill(pid_t pid, int signum) {
  int res = kill(pid, signum);
  checkNeg(res, "kill");
}

//*****************************************************************************
// SIGNAL HANDLER
//*****************************************************************************

void h (int signum) {
   sig = signum;
}

//*****************************************************************************
// CHILD HANDLER
//*****************************************************************************

void child_handler () {
   // armement des signaux ISGUSR1, SIGUSR2 et SIGQUIT
   ssigaction(SIGUSR1, &h);
   ssigaction(SIGUSR2, &h);
   ssigaction(SIGQUIT, &h);

   bool ok = true;
   bool state = true;

   // déblocage temporaire des signaux SIGUSR1, SIGUSR2 et SIGQUIT
   // et suspension du processus en attendant la réception 
   // d'un de ces signaux
   sigset_t set;
   ssigfillset(&set);
   ssigdelset(&set, SIGUSR1);
   ssigdelset(&set, SIGUSR2);
   ssigdelset(&set, SIGQUIT);
   sigsuspend(&set);

   while (sig != SIGQUIT) {
      // vérification de l'alternance de signaux SIGUSR1 et SIGUSR2
      bool is_usr1 = sig == SIGUSR1;
      ok = ok && state == is_usr1;
      state = !state;
      printf("[signal %s reçu par la fils]\n", is_usr1 ? "SIGUSR1" : "SIGUSR2");

      // déplocage temporaire des signaux et suspension du processus
      sigsuspend(&set);
   }
  
   printf("[signal SIGQUIT reçu par le fils]\n");
   if (ok && state) {
      printf("yes\n");
   } else {
      printf("no\n");
   }
}

//*****************************************************************************
// MAIN FUNCTION
//*****************************************************************************

int main () {
   // blocage des signaux SIGUSR1, SIGUSR2 et SIGQUIT
   sigset_t set;
   ssigemptyset(&set);
   ssigaddset(&set, SIGUSR1);
   ssigaddset(&set, SIGUSR2);
   ssigaddset(&set, SIGQUIT);
   ssigprocmask(SIG_BLOCK, &set, NULL);

   // création du fils
   pid_t cid = fork_and_run(&child_handler);

   char buff[2];
   int res = sread(0, buff, 2);
   while (res != 0) {
      if (buff[0] == 'q') {
         // envoi d'un signal SIGUSR1 au fils
         skill(cid, SIGUSR1);      
      } else {
         // envoi d'un signal SIGUSR2 au fils
         skill(cid, SIGUSR2);      
      }
      sleep(1);
      res = sread(0, buff, 2);
   }

   // envoi d'un signal SIGQUIT au fils
   skill(cid, SIGQUIT);

   // attente de la fin du fils
   swaitpid(cid, NULL);
}
