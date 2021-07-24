//#include "../2/chat.h"

#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#define LEN 2048

// Global variables.
volatile sig_atomic_t flag = 0;
int sockfd = 0;
char name[32];

void str_trim_lf(char* arr, int length)// trim \n
{
    int i;
    for (i = 0; i < length; i++)
	{
	    if (arr[i] == '\n')
		{
			arr[i] = '\0';
			break;
		}
	}
}

void catch_ctrl_c_and_exit(int sig)
{
	flag = 1;
}

//or_
void send_msg_handler()
{
	char st[LEN] = {};
	char buffer[LEN + 32] = {};
	while(1)
	{
//		stout();
		fgets(st, LEN, stdin);
		str_trim_lf(st, LEN);

		if (strcmp(st, "exit") == 0 || st[0]=='\0')
		{
			break;
    	}
		else
		{
			sprintf(buffer, "%s: %s \n", name, st);
			send(sockfd, buffer, strlen(buffer), 0);
		}
		bzero(st, LEN);
		bzero(buffer, LEN + 32);
	}
	flag=1;
}

void recv_msg_handler()
{
	char baf[LEN] = {};
	while (1)
	{
		int receive = recv(sockfd, baf, LEN, 0);
    	if (receive > 0)
		{
    		printf("%s", baf);
//    		stout();
    	}
		else if (receive == 0)
		{
			break;
    	}
		else
		{
			perror("recv");
		}
		memset(baf, 0, sizeof(baf));
	}
}

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Usage: %s <port>\n", argv[0]);
		return 0;
	}

	char *ip = "127.0.0.1";
	int port = atoi(argv[1]);

	signal(SIGINT, catch_ctrl_c_and_exit);

	printf("Please enter your name: ");
	fgets(name, 32, stdin);
	str_trim_lf(name, strlen(name));


	if (strlen(name) > 32 || strlen(name) < 2)
	{
		printf("Name must be less than 30 and more than 2 characters.\n");
		return 0;
	}

	struct sockaddr_in server_addr;

	/* Socket settings */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(ip);
	server_addr.sin_port = htons(port);


  // Connect to Server
	if ((connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr))) == -1)
	{
		perror("client: connect");
		return 0;
	}

	// Send name
	send(sockfd, name, 32, 0);

	printf("	WELCOME :)\n");

	pthread_t send_msg;
	if(pthread_create(&send_msg, NULL, (void *) send_msg_handler, NULL) != 0)
	{
		perror("client: pthread");
		return 0;
	}

	pthread_t recv_msg;
	if(pthread_create(&recv_msg, NULL, (void *) recv_msg_handler, NULL) != 0){
		perror("client: pthread");
		return 0;
	}

	while (1){
		if(flag){
			printf("\n Good Bye :)\n");
			break;
    }
	}

	close(sockfd);

	return 0;
}
