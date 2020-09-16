#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <poll.h>

#define BUFFERSIZE 50
#define TIMEMILLISEC 10000
#define NB_CHILD 2

static void check_neg(int ret, char *message)
{
	if (ret < 0)
	{
		perror(message);
		exit(EXIT_FAILURE);
	}
}

static pid_t fork_and_run(void (*handler)(int *), int *pipe)
{
	pid_t pid = fork();
	check_neg(pid, "Fork failed\n");
	if (pid == 0)
	{
		(*handler)(pipe);
		exit(EXIT_SUCCESS);
	}
	else
		return pid;
}

static void child_trt(int *pipe)
{
	int ret, i;
	char buffer[BUFFERSIZE];

	srand(getpid());
	ret = close(pipe[0]);
	check_neg(ret, "close pipe[0] child");

	for (i = 0; i < 10; i++)
	{
		// alea
		int alea = rand() % TIMEMILLISEC;
		// stop process nb sec
		usleep(alea);

		sprintf(buffer, "Fils %i : inscription %i\n", getpid(), alea);
		ret = write(pipe[1], buffer, strlen(buffer));
		check_neg(ret, "write child pipe");
	}
	ret = close(pipe[1]);
	check_neg(ret, "close child pipe[1]");
}

int main(int argc, char **argv)
{
	int pidInscr1, pidInscr2;
	int pipeInscr1[2], pipeInscr2[2];
	int ret;
	char buffer[BUFFERSIZE];
	fd_set fdset;
	int nbChar;
	int i;
	struct pollfd fds[NB_CHILD];

	// pipe init
	ret = pipe(pipeInscr1);
	check_neg(ret, "pipe Inscr1");

	pidInscr1 = fork_and_run(child_trt, pipeInscr1);
	check_neg(pidInscr1, "fork Inscr1");

	ret = pipe(pipeInscr2);
	check_neg(ret, "pipe Inscr2");
	pidInscr2 = fork_and_run(child_trt, pipeInscr2);
	check_neg(pidInscr2, "fork Inscr2");

	ret = close(pipeInscr1[1]);
	check_neg(ret, "close parent pipeInscr1[1]");
	ret = close(pipeInscr2[1]);
	check_neg(ret, "close parent pipeInscr2[1]");

	// init poll
	fds[0].fd = pipeInscr1[0];
	fds[0].events = POLLIN;

	fds[1].fd = pipeInscr2[0];
	fds[1].events = POLLIN;

	while (1)
	{
		ret = poll(fds, 2, 0);
		check_neg(ret, "erreur poll");

		if (fds[0].revents & POLLIN)
		{
			nbChar = read(pipeInscr1[0], buffer, BUFFERSIZE);
			check_neg(nbChar, "read parent pipeInscr1");

			nbChar = write(1, buffer, nbChar);
			check_neg(nbChar, "write parent stdout");
		}

		if (fds[1].revents & POLLIN)
		{
			nbChar = read(pipeInscr2[0], buffer, BUFFERSIZE);
			check_neg(nbChar, "read parent pipeInscr1");

			nbChar = write(1, buffer, nbChar);
			check_neg(nbChar, "write parent stdout");
		}
	}
}
