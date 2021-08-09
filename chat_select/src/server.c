#include "../include/chat.h"
#include "../include/server.h"

int listenfd = 0;
char *ip = "127.0.0.1";
int option = 1;
struct sockaddr_in serv_addr;
bool work;
int port;

client_t *clients[MAX_CLIENTS];
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void get_timestamp(char *dt)
{
    struct tm tm;
    time_t current_time;
    current_time = time(NULL);
    tm = *localtime(&current_time); // convert time_t to struct tm
    strftime(dt, 20, LOG_TIME_FORMAT, &tm); // format
}

void print_log(char *msg)
{
    char dt[20];
    get_timestamp(dt);

    /* Write to log file */
    FILE *fd;
    fd = fopen (LOGFILE, "a+");
    if (fd == NULL)
	{
       printf("failed to open server.log\n");
    }

    fprintf (fd, "[%s] in [%d] %s\n", dt, port, msg);
    fclose (fd);
}


void printclient(struct sockaddr_in addr)
{
	printf("%d.%d.%d.%d",
        addr.sin_addr.s_addr & 0xff,
        (addr.sin_addr.s_addr & 0xff00) >> 8,
        (addr.sin_addr.s_addr & 0xff0000) >> 16,
        (addr.sin_addr.s_addr & 0xff000000) >> 24);
}

//Add clients to queue.
void queue_add(client_t *cl)
{
	pthread_mutex_lock(&clients_mutex);
	work = true;
	for(int i=0; i < MAX_CLIENTS && work; ++i)
	{
		if(!clients[i])
		{
			clients[i] = cl;
			work = false;
		}
	}
	pthread_mutex_unlock(&clients_mutex);
}

//Remove clients to queue.
void queue_remove(int uid)
{
	pthread_mutex_lock(&clients_mutex);
	work = true;
	for(int i=0; i < MAX_CLIENTS && work; ++i)
	{
		if(clients[i])
		{
			if(clients[i]->uid == uid)
			{
				clients[i] = NULL;
				work = false;
			}
		}
	}

	pthread_mutex_unlock(&clients_mutex);
}

//Send message to all clients except sender.
void sendinfo(char *s, int uid, char room)
{
	pthread_mutex_lock(&clients_mutex);
	work = true;

	for(int i=0; i<MAX_CLIENTS && work; ++i)
	{
		if(clients[i])
		{
			if(clients[i]->uid != uid && clients[i]->room == room)
			{
				if(write(clients[i]->sockfd, s, strlen(s)) < 0)
				{
					perror("server: write to descriptor failed");
					work = false;
				}
			}
		}
	}

	pthread_mutex_unlock(&clients_mutex);
}

//Handle all communication with the client.
int handle_client(void *arg)
{
	char buff[LEN];
	char name[32];
	char room[3];
	int leave_flag = 0;

	cli_count++;
	client_t *cli = (client_t *)arg;
	
//	printf("123");

	bzero(buff, LEN);

	int receive = recv(cli->sockfd, buff, LEN, 0);

	if(buff[0] == '1')
	{
		printf("1\n");
		// Name
		if((receive <= 0 || strlen(buff) <  2 || strlen(buff) >= 32-1))
		{
			printf("Enter your name.\n");
			leave_flag = 1;
		}
		else
		{
			strcpy(cli->name, name + 1);
		}
		return 1;
	}
	if(buff[0] == 'r')
	{
		recv(cli->sockfd, room, 2, 0);
		printf("room [%s]\n",room);
		if(room[1] == '1' || room[1] == '2' || room[1] == '3')
		{
			cli->room = room[1];
		}
		print_log(room);
		sprintf(buff, "%s has joined room [%c] \n", cli->name,cli->room);
		print_log(buff);
		printf("%s", buff);
		sendinfo(buff, cli->uid, cli->room);
		return 2;
	}



//	while(!leave_flag)// or
	{
		if (receive > 0)
		{
			if(strlen(buff) > 0)
			{
				sendinfo(buff, cli->uid,cli->room);
				str_trim_lf(buff, strlen(buff));
				printf("%s\n", buff);
			}
		}
		else if (receive == 0 || strcmp(buff, "~exit~") == 0)
		{
			sprintf(buff, "%s has left\n", cli->name);
			printf("%s", buff);
			print_log(buff);
			sendinfo(buff, cli->uid,cli->room);
			leave_flag = 1;
		}
		else
		{
			printf("server: -1\n");
			leave_flag = 1;
			close(cli->sockfd);
			free(cli);
			cli_count--;
		}

		bzero(buff, LEN);
	}

	//Delete client from queue and yield thread.
//	close(cli->sockfd);
//	free(cli);
//	cli_count--;
//
//	pthread_exit(0);

	return 0;
}
int prepar_socket()
{
	//Socket settings
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(ip);
	serv_addr.sin_port = htons(port);

	//Ignore pipe signals
	signal(SIGPIPE, SIG_IGN);

	if(setsockopt(listenfd, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), (char*)&option, sizeof(option)) < 0)
	{
		perror("server: setsockopt failed");
		return 0;
	}
	//Bind
	if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
	{
    	perror("server: Socket binding failed");
    	return 0;
	}

	//Listen
	if (listen(listenfd, 10) < 0)
	{
    	perror("server: Socket listening failed");
    	return 0;
	}
	return 1;
}

