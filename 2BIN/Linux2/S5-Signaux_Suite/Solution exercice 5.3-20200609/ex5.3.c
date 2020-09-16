#include <stdbool.h>
#include <stdio.h>

#include <signal.h>

#include <sys/types.h>

#include <unistd.h>

#include "utils.h"

#define TIMER 5

//***************************************************************************
// CHILD CODE
//***************************************************************************

volatile int signum;

void handler(int num) {
	signum = num;
}

void run() {
	ssigaction(SIGUSR2, handler);
	
	sigset_t set;
	ssigfillset(&set);
	ssigdelset(&set, SIGUSR1);
	ssigdelset(&set, SIGUSR2);
	
	sigsuspend(&set);
	
	pid_t ppid = getppid();
	int cpt = 0;
	while(signum != SIGUSR2) {
		skill(ppid, SIGUSR1);
		cpt++;
		sigsuspend(&set);
	}
	
	printf("[PID = %d] #SIGUSR1 RECEIVED = %d\n", getpid(), cpt);
}

//***************************************************************************
// PARENT CODE
//***************************************************************************

int main () {
	sigset_t set1;
	ssigfillset(&set1);
	ssigprocmask(SIG_BLOCK, &set1, NULL);

	ssigaction(SIGUSR1, handler);
	
	pid_t chid = fork_and_run0(run);
	
	ssigaction(SIGALRM, handler);
	alarm(TIMER);

	sigset_t set2;
	ssigfillset(&set2);
	ssigdelset(&set2, SIGUSR1);
	ssigdelset(&set2, SIGALRM);

	int cpt = 1;
	skill(chid, SIGUSR1);
	sigsuspend(&set2);
	while(signum != SIGALRM) {
		cpt++;
		skill(chid, SIGUSR1);
		sigsuspend(&set2);
	}
	
	skill(chid, SIGUSR2);
	printf("[PID = %d] #SIGUSR1 SEND = %d\n", getpid(), cpt);
	swaitpid(chid, NULL, 0);
}