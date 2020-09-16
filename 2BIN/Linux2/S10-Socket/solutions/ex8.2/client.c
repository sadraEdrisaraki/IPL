#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "check.h"
#include "utils.h"


#define BUFFER_SIZE 1024


int initSocketClient(char ServerIP[16], int Serverport)
{
	int sockfd;
	int ret;
	struct sockaddr_in addr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	checkNeg(sockfd,"socket client creation error");

	memset(&addr,0,sizeof(addr)); /* en System V */
	addr.sin_family = AF_INET;
	addr.sin_port = htons(Serverport);
	addr.sin_addr.s_addr = inet_addr(ServerIP);
	ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
	checkNeg(ret,"connect client error");
	
	return sockfd;
}



int main (int argc, char ** argv)
{
	int sockfd;
	int ret, nbChar;
	char ligne [BUFFER_SIZE];
	char request[BUFFER_SIZE];
	char ip[18];
	char response[BUFFER_SIZE]; 
	char pageName[BUFFER_SIZE];	
	int fdHTMLPage;


	int fdSiteMap = open("sitemap.txt",O_RDONLY);
	checkNeg(fdSiteMap,"open sitemap error");

	hostname_to_ip("ochoquet.be",ip);
	printf("IPv4 ochoquet.be : %s\n",ip );
	

	while (readline(fdSiteMap,ligne))
	{
		printf("Ligne : %s ,strlen :%lu\n",ligne, strlen(ligne));

		sprintf(pageName,"%s",strrchr(ligne,'/')+1);
		printf("Page Name : %s\n", pageName);

		sockfd = initSocketClient(ip, 80);
		checkNeg(sockfd,"socket init client error");

		sprintf(request,"GET %s HTTP/1.0\r\nHost: %s\r\n\r\n",ligne,"ochoquet.be");
		ret = write (sockfd,request,strlen(request));
		checkNeg(ret,"write request error");
		fdHTMLPage = open(pageName,O_RDWR | O_TRUNC | O_CREAT,0644);
		checkNeg(fdHTMLPage,"error open fdHTMLPage");
		while ((nbChar = read(sockfd,response, BUFFER_SIZE)))
		{
			checkNeg(nbChar,"error read response");
			write(fdHTMLPage,response,nbChar);
			
		}
		ret = close(sockfd);
		checkNeg(ret,"error close sockfd");
		ret = close(fdHTMLPage);
		checkNeg(ret,"error close fdHTMLPage");

	}

	
}
