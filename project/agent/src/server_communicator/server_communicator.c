#include "../../include/server_communicator/server_commumicator.h"
#include "../../include/agent.h"

// Global variables.
volatile sig_atomic_t flag = 0;
int sockfd = 0;

void catch_ctrl_c_and_exit(int sig)
{
	flag = 1;
}

void send_msg_handler(char* str)
{
	bool work1 = true;
	while(work1)
	{
		if (strcmp(str, "~exit~") == 0 )
		{
			work1 = false;
    	}
		else
		{
			send(sockfd, str, strlen(str), 0);
		}
		if (work1)
		{
			bzero(str, strlen(str));
		}
	}
	flag=1;
}

int connection(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Usage: %s <port>\n", argv[0]);
		return 0;
	}
	
	p_packet p_pack = NULL;
	
	char *ip = "127.0.0.1";
	int port = atoi(argv[1]);

	signal(SIGINT, catch_ctrl_c_and_exit);

	struct sockaddr_in server_addr;

	//Socket settings
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(ip);
	server_addr.sin_port = htons(port);

	//Connect to Server
	if((connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr))) == -1)
	{
		perror("client: connect");
		return 0;
	}
	return 1;
}

int main(int argc, char **argv)
{
	if((connection(argc, argv)) == 0)
	{
		return 0;
	}
	
	int sock1 = prepare_socket();//Preparing to open the socket.
	int s1;
	char *str = "";
	if(sock1 == -1)
	{
		return 0;
	}

	pthread_t add;
	if(pthread_create(&add, NULL, (void *) recv_packet, (int *) sock1)!= 0)
	{
		perror("pthread recv_packet");
		return 0;
	}

	pthread_t hendel;
	if(pthread_create(&hendel, NULL, (void *) hendler_packet, NULL)!= 0)
	{
		perror("pthread hendler_packet");
		return 0;
	}

	pthread_t sec;
	if(pthread_create(&sec, NULL, (void *) secend,NULL) != 0)
	{
		perror("pthread secend");
		return 0;
	}
	
//	pthread_t send_msg;
//	if(pthread_create(&send_msg, NULL, (void *) send_msg_handler, (char *)str) != 0)
//	{
//		perror("client: pthread");
//		return 0;
//	}
	
	while(1)
	{
		bool work1 = true;
		if(work && num!=0)
		{
//			int number = dictionary_size;
			char *data[dictionary_size + 1];
			char **all = send_data(data);
			printf("____________________________________________\n");
			int size_of_dictionary = dictionary_size1;
			printf("dictionary_size = %d\n\n",size_of_dictionary);
			for(int i = 0; i <= size_of_dictionary; i++)
			{
				if (strcmp(all[i], "~exit~") == 0 )
				{
					work1 = false;
	    		}
				else
				{
					send(sockfd, all[i], strlen(all[i]), 0);
				}
				if (work1)
				{
					bzero(all[i], strlen(all[i]));
				}
			}
			
			printf("____________________________________________\n");
		}
	}
//
//	while (1)
//	{
//		if(flag)
//		{
//			printf("\n Good Bye :)\n");
//			close(sockfd);
//			return 0;
//    	}
//	}
}
