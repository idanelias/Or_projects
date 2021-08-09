#include "../include/chat.h"
#include "../include/server.h"

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char **argv)
{
	//client_t *cli = (client_t *)malloc(sizeof(client_t));
	if(argc != 2)
	{
		printf("Usage: %s <port>\n", argv[0]);
		return 0;
	}

	port = atoi(argv[1]);
	int connfd = 0;
	struct sockaddr_in cli_addr;
	pthread_t tid;

	if(prepar_socket() == 0)
	{
		return 0;
	}

	printf("	WELCOME :)\n");

/*
	while(1)
	{
		socklen_t clilen = sizeof(cli_addr);
		connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &clilen);

		//Check if max clients is reached.
		if((cli_count + 1) == MAX_CLIENTS)
		{
			printf("Max clients reached. Rejected: ");
			printclient(cli_addr);
			printf(":%d\n", cli_addr.sin_port);
			close(connfd);
		}
		else
		{
			//Client settings
		//	free(*cli);
			client_t *cli = (client_t *)malloc(sizeof(client_t));
			cli->address = cli_addr;
			cli->sockfd = connfd;
			cli->uid = uid++;

			//Add client to the queue and fork thread.
			queue_add(cli);
			pthread_create(&tid, NULL, &handle_client, (void*)cli);//or

			//Reduce CPU usage.
			sleep(1);
		}
	}*/
//	}/////for

	int max = 0;

	fd_set current_sockets, ready_sockets;
	
	while(1)
	{
		
		FD_ZERO(&current_sockets);
		FD_SET(listenfd, &current_sockets);

 		max = listenfd;
		
//		ready_sockets = current_sockets;

//		printf("1\n");
		
		
//		printf("select\n");
		
		for(int j = 0; j <= max; j++)
		{
			if(select(max + 1 + j, &current_sockets, NULL, NULL, NULL) <= 0)
			{
				perror("server select:");
				return 0;
			}
			// send to everyone!
			if (FD_ISSET(j, &ready_sockets))
			{
				client_t *cli = (client_t *)malloc(sizeof(client_t));
				// except the listener and ourselves
				if (j == listenfd)
				{
//					printf("j == listenfd\n");
					socklen_t clilen = sizeof(cli_addr);
					connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &clilen);
					
//					printf("a\n");
					
					//Check if max clients is reached.
					if((cli_count + 1) == MAX_CLIENTS)
					{
						printf("Max clients reached. Rejected: ");
						printclient(cli_addr);
						printf(":%d\n", cli_addr.sin_port);
						close(connfd);
					}
					else
					{
						//Client settings
						//	free(*cli);
						cli->address = cli_addr;
						cli->sockfd = connfd;
						cli->uid = uid++;
					}
					FD_SET(connfd, &current_sockets);
					if (connfd > max)
					{
						max = connfd;
					}
//					printf("handle_client\n");
					if(handle_client((void*)cli) == 0)
					{
						printf("return 0");
					}
					printf("handle_client\n");
					FD_CLR(j,&current_sockets);
				}
				else
				{
//					printf("handle_client\n");
					//handle_client((void*)cli);
					printf("FD_CLR\n");
					FD_CLR(j,&current_sockets);
				}
				printf("123");
				
			}
		}
//			sleep(1);
	}
	printf("123456");
	return 0;
}
