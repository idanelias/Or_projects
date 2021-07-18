// Client side implementation of UDP client-server model
#include "../include/udp.h"

int sendsrt(char *buf ,int sockfd,struct sockaddr_in servaddr)	//Send to the server.
{
	sendto(sockfd, (const char *)buf, strlen(buf), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr));
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
	n = recvfrom(sockfd, (char *)buf, MAXLINE, 0, (struct sockaddr *) &servaddr, &len);
	buf[n] = '\0';
	printf("Server -> Client \n");
	printf("%s\n", buf);
}

void memsetfunc(struct sockaddr_in *addr)
{
	memset(addr, 0, sizeof(&addr));
 	printf("123");
 	
 	
	// Filling server information
	addr->sin_family = AF_INET;
	addr->sin_port = htons(PORT);
	addr->sin_addr.s_addr = INADDR_ANY;
//	printf("456");
}

int sock()
{
	int sockfd;
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1 )
	{
		perror("socket creation failed");
	}
	return sockfd;
}

// Driver code
int main(char *argv[]) {
	int sockfd;
	char buf[MAXLINE];
	struct sockaddr_in servaddr;
	
	// Creating socket file descriptor
	sockfd = sock();
	if ( sockfd  == -1 )
	{
		return 0;
	}

	memsetfunc(&servaddr);


//	filling(servaddr);
 // Filling server information
//	servaddr.sin_family = AF_INET;
//	servaddr.sin_port = htons(PORT);
//	servaddr.sin_addr.s_addr = INADDR_ANY;


	
	int n, len;
	while(1)
	{
		printf("\nClient:\n");
		fgets(buf,sizeof(buf),stdin);
		//Send to the server.
		if(sendsrt(buf,sockfd,servaddr)==0)
		{
			return 0;
		}
		
		receives(buf,sockfd,servaddr);//Receives from the server.
	}
	

	close(sockfd);
	return 0;
}

