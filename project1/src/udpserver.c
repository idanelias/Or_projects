// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 4080 //The port number.
#define MAXLINE 1024//The maximum lengh to the string.

void sendsrt(char *buf ,int sockfd,struct sockaddr_in cliaddr, int len)//Send to client.
{
	sendto(sockfd, (const char *)buf, strlen(buf), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
	printf("Server -> Client \n");
	printf("%s\n\n", buf);
}

// Driver code
int main() {
	int sockfd;
	char buf[MAXLINE];
	struct sockaddr_in servaddr, cliaddr;
	int len, n;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1 )
	{
		perror("socket creation failed");
		return 0;
	}

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));

	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);

	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) == -1 )
	{
		perror("bind failed");
		return 0;
	}

	len = sizeof(cliaddr); //len is value/resuslt
	
	int b = 1;
	while(b)
	{
		printf("\n\n\nServer:\n");

		//Receives from the server.
		n = recvfrom(sockfd, (char *)buf, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
		buf[n] = '\0';
		if(buf[0]=='\n')
		{
			return 0;
		}
		printf("Client -> Server \n");
		printf("%s\n", buf);
		
		////Send to the client.
		sendsrt(buf ,sockfd ,cliaddr ,len);

	}
	

	return 0;
}

