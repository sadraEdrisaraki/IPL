#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <poll.h>

#define BUFFERSIZE 50
#define TIMEMILLISEC 10000
#define NB_CHILD 3

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
	int pidChild[NB_CHILD];
	int pipeChild[NB_CHILD][2];
	int ret;
	char buffer[BUFFERSIZE];
	fd_set fdset;
	int nbChar;
	int i;
	struct pollfd fds[NB_CHILD];

	for (int i = 0; i < NB_CHILD; i++)
	{
		// pipe init
		ret = pipe(pipeChild[i]);
		check_neg(ret, "pipe Inscr");

		pidChild[i] = fork_and_run(child_trt, pipeChild[i]);
		check_neg(pidChild[i], "fork Inscr");

		ret = close(pipeChild[i][1]);
		check_neg(ret, "close parent pipeInscr1[1]");

		// init poll

		fds[i].fd = pipeChild[i][0];
		fds[i].events = POLLIN;

	}

	while (1)
	{
		ret = poll(fds, NB_CHILD, 0);
		check_neg(ret, "erreur poll");

		for (int i = 0; i < NB_CHILD; i++)
		{
			if (fds[i].revents & POLLIN)
			{
				nbChar = read(pipeChild[i][0], buffer, BUFFERSIZE);
				check_neg(nbChar, "read parent pipeInscr1");

				nbChar = write(1, buffer, nbChar);
				check_neg(nbChar, "write parent stdout");
			}
		}
	}
}
