// Client side implementation of UDP client-server model

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 4080 //The port number.
#define MAXLINE 1024 //The maximum lengh to the string.

int sendsrt(char *buf ,int sockfd,struct sockaddr_in servaddr)	//Send to the server.
{
	sendto(sockfd, (const char *)buf, strlen(buf), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
  	if(buf[0]=='\n')
	{
		printf("close\n");
		close(sockfd);
		return 0;
	}
	printf("Client -> Server \n");
	printf("%s\n", buf);
	return 1;
}

void receives(char *buf,int sockfd,struct sockaddr_in servaddr)//Receives from the server.
{
	int n, len;
	n = recvfrom(sockfd, (char *)buf, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
	buf[n] = '\0';
	printf("Server -> Client \n");
	printf("%s\n", buf);
}

// Driver code
int main(char *argv[]) {
	int sockfd;
	char buf[MAXLINE];
	struct sockaddr_in servaddr;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1 )
	{
		perror("socket creation failed");
		return 0;
	}

	memset(&servaddr, 0, sizeof(servaddr));

	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	
	int n, len;
	while(1)
	{
		printf("\n\n\nClient:\n");
		fgets(buf,sizeof(buf),stdin);
		//Send to the server.
		if(sendsrt(buf,sockfd,servaddr)==0)
		{
			return 0;
		}
		else {
			printf("server not found\n");
		}
		
		receives(buf,sockfd,servaddr);//Receives from the server.
	}
	

	close(sockfd);
	return 0;
}

