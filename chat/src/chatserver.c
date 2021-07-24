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

#define MAX_CLIENTS 100
#define LEN 2048


static _Atomic unsigned int cli_count = 0;
static int uid = 10;

/* Client structure */
typedef struct
{
	struct sockaddr_in address;
	int sockfd;
	int uid;
	char name[32];
} client_t;

client_t *clients[MAX_CLIENTS];

pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void str_trim_lf (char* arr, int length)
{
	int i;
	for (i = 0; i < length; i++)// trim \n
	{
		if (arr[i] == '\n')
		{
      		arr[i] = '\0';
      		break;
    	}
  	}
}

void printclient(struct sockaddr_in addr)
{
	printf("%d.%d.%d.%d",
        addr.sin_addr.s_addr & 0xff,
        (addr.sin_addr.s_addr & 0xff00) >> 8,
        (addr.sin_addr.s_addr & 0xff0000) >> 16,
        (addr.sin_addr.s_addr & 0xff000000) >> 24);
}

/* Add clients to queue */
void queue_add(client_t *cl)
{
	pthread_mutex_lock(&clients_mutex);

	for(int i=0; i < MAX_CLIENTS; ++i)
	{
		if(!clients[i])
		{
			clients[i] = cl;
			break;
		}
	}
	pthread_mutex_unlock(&clients_mutex);
}

//Remove clients to queue
void queue_remove(int uid)
{
	pthread_mutex_lock(&clients_mutex);

	for(int i=0; i < MAX_CLIENTS; ++i)
	{
		if(clients[i])
		{
			if(clients[i]->uid == uid)
			{
				clients[i] = NULL;
				break;
			}
		}
	}

	pthread_mutex_unlock(&clients_mutex);
}

//Send message to all clients except sender
void sendinfo(char *s, int uid)
{
	pthread_mutex_lock(&clients_mutex);

	for(int i=0; i<MAX_CLIENTS; ++i)
	{
		if(clients[i])
		{
			if(clients[i]->uid != uid)
			{
				if(write(clients[i]->sockfd, s, strlen(s)) < 0){
					perror("server: write to descriptor failed");
					break;
				}
			}
		}
	}

	pthread_mutex_unlock(&clients_mutex);
}

/* Handle all communication with the client */
void *handle_client(void *arg)
{
	char buff[LEN];
	char name[32];
	int leave_flag = 0;

	cli_count++;
	client_t *cli = (client_t *)arg;

	// Name
	if(recv(cli->sockfd, name, 32, 0) <= 0 || strlen(name) <  2 || strlen(name) >= 32-1)
	{
		printf("Enter yore name.\n");
		leave_flag = 1;
	}
	else
	{
		strcpy(cli->name, name);
		sprintf(buff, "%s has joined\n", cli->name);
		printf("%s", buff);
		sendinfo(buff, cli->uid);
	}

	bzero(buff, LEN);//

	while(1)
	{
		if (leave_flag)
		{
			break;
		}

		int receive = recv(cli->sockfd, buff, LEN, 0);
		if (receive > 0)
		{
			if(strlen(buff) > 0)
			{
				sendinfo(buff, cli->uid);
				str_trim_lf(buff, strlen(buff));
				printf("%s\n", buff);
			}
		}
		else if (receive == 0 || strcmp(buff, "exit") == 0)
		{
			sprintf(buff, "%s has left\n", cli->name);
			printf("%s", buff);
			sendinfo(buff, cli->uid);
			leave_flag = 1;
		}
		else
		{
			printf("server: -1\n");
			leave_flag = 1;
		}

		bzero(buff, LEN);
	}

  /* Delete client from queue and yield thread */
	close(cli->sockfd);
	queue_remove(cli->uid);
	free(cli);
	cli_count--;
	pthread_detach(pthread_self());

	return NULL;
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
	int option = 1;
	int listenfd = 0, connfd = 0;
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;
	pthread_t tid;

  /* Socket settings */
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(ip);
  serv_addr.sin_port = htons(port);

  /* Ignore pipe signals */
	signal(SIGPIPE, SIG_IGN);

	if(setsockopt(listenfd, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), (char*)&option, sizeof(option)) < 0)
	{
		perror("server: setsockopt failed");
		return 0;
	}

	/* Bind */
	if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
	{
    	perror("server: Socket binding failed");
    	return 0;
	}

  /* Listen */
	if (listen(listenfd, 10) < 0)
	{
    	perror("server: Socket listening failed");
    	return 0;
	}

	printf("	WELCOME :)\n");

	while(1)
	{
		socklen_t clilen = sizeof(cli_addr);
		connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &clilen);

		/* Check if max clients is reached */
		if((cli_count + 1) == MAX_CLIENTS)
		{
			printf("Max clients reached. Rejected: ");
			printclient(cli_addr);
			printf(":%d\n", cli_addr.sin_port);
			close(connfd);
			continue;
		}

		/* Client settings */
		client_t *cli = (client_t *)malloc(sizeof(client_t));
		cli->address = cli_addr;
		cli->sockfd = connfd;
		cli->uid = uid++;

		/* Add client to the queue and fork thread */
		queue_add(cli);
		pthread_create(&tid, NULL, &handle_client, (void*)cli);

		/* Reduce CPU usage */
		sleep(1);
	}

	return 0;
}
