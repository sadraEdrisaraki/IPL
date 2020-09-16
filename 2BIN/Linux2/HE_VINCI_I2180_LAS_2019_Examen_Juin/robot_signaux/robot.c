#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <sys/types.h>

#include <unistd.h>

#include "utils.h"

#define MAX_Y  10

#define READ_SIZE	2

//***************************************************************************
// CHILD CODE
//***************************************************************************

int signum;

void handler(int num) {
	signum = num;
}

void run() {
	int x = 0;
	int y = 0;
	printf("X = %d , Y = %d\n",x,y);
	// armement signaux
	ssigaction(SIGUSR1, handler);
	ssigaction(SIGUSR2, handler);

	// déblocage temporaire des signaux 
	sigset_t set;
	ssigfillset(&set);
	ssigdelset(&set, SIGUSR1);
	ssigdelset(&set, SIGUSR2);
	sigsuspend(&set); // attente d'un signal correspondant

	while (1) {
		if (signum == SIGUSR1) { // vers le nord ; modifié Y
			y++;
			if (y == MAX_Y) {
				y = 0;
			}
		} else if (signum == SIGUSR2) { // Vers le sud ; modifie Y
			y--;
			if (y == -1) {
				y = 9;
			}
		}
		printf("X = %d , Y = %d\n",x,y);
		sigsuspend(&set);
	}
}

//***************************************************************************
// PARENT CODE
//***************************************************************************

int main () {

	// Blocage des signaux
	sigset_t set;
	ssigemptyset(&set);
	ssigaddset(&set, SIGUSR1);
	ssigaddset(&set, SIGUSR2);

	ssigprocmask(SIG_BLOCK, &set, NULL);

	swrite(1, ">>>", 3);
	pid_t child = fork_and_run0(run);

	char buff[READ_SIZE];
	int res = sread(0, buff, READ_SIZE);
	while(res != 0) {

		if (buff[0] == 'U') { 
			skill(child, SIGUSR1);
		} else if (buff[0] == 'D') {
			skill(child, SIGUSR2);
		} else if (buff[0] == 'Q') {
			skill(child, SIGKILL);
			break;
		}

		swrite(1, "\n>>>", 4);
		res = sread(0, buff, READ_SIZE);
	}

	swaitpid(child, NULL, 0);
	exit(0);
}

