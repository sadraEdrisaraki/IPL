#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>

#define BUFFERSIZE 50
#define TIMEMILLISEC 10000 

void testSysCall(int val, char * msg)
{
	if (val == -1)
	{
		char message[256];
		sprintf(message,"Erreur appel système : %s", msg); 
		perror(message); 
        exit(EXIT_FAILURE);
	}
}


int main (int argc, char ** argv)
{
	int pidInscr1, pidInscr2;	 	
	int pipeInscr1[2], pipeInscr2[2];
	int ret;
	char buffer[BUFFERSIZE];
	fd_set fdset;
	int nbChar;
	int i;

	// pipe init
	ret = pipe(pipeInscr1);
	testSysCall(ret,"pipe Inscr1");
	ret = pipe(pipeInscr2);
	testSysCall(ret,"pipe Inscr2");
	 
	pidInscr1 = fork();
	testSysCall(pidInscr1,"fork Inscr1");
	
	// parent
	if (pidInscr1)
	{
		pidInscr2 = fork();
		testSysCall(pidInscr2,"fork Inscr2");
        
		// parent
		if (pidInscr2)
		{
			ret = close(pipeInscr1[1]);
			testSysCall(ret,"close parent pipeInscr1[1]");
			ret = close(pipeInscr2[1]);
			testSysCall(ret,"close parent pipeInscr2[1]");
			// init select
			FD_ZERO(&fdset);	
			FD_SET(pipeInscr1[0],&fdset);
			FD_SET(pipeInscr2[0],&fdset);
            
			while (1)
			{
				// init select
				FD_ZERO(&fdset);	
				FD_SET(pipeInscr1[0],&fdset);
				FD_SET(pipeInscr2[0],&fdset);
				ret = select(FD_SETSIZE,&fdset,NULL,NULL,NULL);
				testSysCall(ret,"select parent");
				if (FD_ISSET(pipeInscr1[0],&fdset))
				{
					nbChar = read(pipeInscr1[0],buffer, BUFFERSIZE);
					testSysCall(nbChar,"read parent pipeInscr1");

					nbChar = write (1,buffer,nbChar);	
					testSysCall(nbChar,"write parent stdout");

				}
				if (FD_ISSET(pipeInscr2[0],&fdset))
				{
					nbChar = read(pipeInscr2[0],buffer, BUFFERSIZE);
					testSysCall(nbChar,"read parent pipeInscr2");
                    
					nbChar = write (1,buffer,nbChar);
					testSysCall(nbChar,"write parent stdout");	
				}
			}
		} 
        // child Inscr2
		else {
            srand(getpid());
			ret = close(pipeInscr2[0]);
			testSysCall(ret,"close Inscr2 pipeInscr2[0]");
			ret = close(pipeInscr1[0]);
			testSysCall(ret,"close Inscr2 pipeInscr1[0]");
			ret = close(pipeInscr1[1]);
			testSysCall(ret,"close Inscr2 pipeInscr1[1]");

			for (i=0;i<10;i++)
			{	
				// alea
				int alea = rand() % TIMEMILLISEC ;
				// stop process nb sec
				usleep(alea);
                
				sprintf(buffer,"Fils2 : inscription %i\n",alea);
				ret = write(pipeInscr2[1],buffer,strlen(buffer));
				testSysCall(ret, "write Inscr1 pipeInscr2");
			}
			ret = close(pipeInscr2[1]);
			testSysCall(ret, "close Inscr2 pipeInscr2[1]");
		}
	}
	// child Inscr1 
	else {
		srand(getpid());
		ret = close(pipeInscr1[0]);
		testSysCall(ret,"close Inscr1 pipeInscr1[0]");
		ret = close(pipeInscr2[0]);
		testSysCall(ret,"close Inscr1 pipeInscr2[0]");
		ret = close(pipeInscr2[1]);
		testSysCall(ret,"close Inscr1 pipeInscr2[1]");
        
		for (i=0;i<10;i++)
		{	
			// alea
			int alea = rand() % TIMEMILLISEC;
			// stop process nb sec
			usleep(alea);

			sprintf(buffer,"Fils1 : inscription %i\n",alea);
			ret = write(pipeInscr1[1],buffer,strlen(buffer));
			testSysCall(ret, "write Inscr1 pipeInscr1");
		}
		ret = close(pipeInscr1[1]);
		testSysCall(ret, "close Inscr1 pipeInscr1[1]");
	}
}
