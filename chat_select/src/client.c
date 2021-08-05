#include "../include/chat.h"
#include "../include/client.h"

volatile sig_atomic_t flag = 0;
int sockfd = 0;
char name[32];
char room[3];

void catch_ctrl_c_and_exit(int sig)
{
	flag = 1;
}

void send_msg_handler()
{
	char st[LEN] = {};
	char buffer[LEN + 32] = {};
	bool work = true;
	while(work)
	{
		strcat(st,"3");
		fgets(st + 1, LEN - 1, stdin);
		str_trim_lf(st, LEN);

		if (strcmp(st, "~exit~") == 0 /*|| st[0]=='\0'*/)
		{
			work = false;
    	}
		else
		{
			sprintf(buffer, "%s: %s \n", name+1, st);
			send(sockfd, buffer, strlen(buffer), 0);
		}
		if (work)
		{
			bzero(st, LEN);
			bzero(buffer, LEN + 32);
		}
	}
	flag=1;
}

//Receive message.
void recv_msg_handler()
{
	char baf[LEN] = {};
	bool work = true;
	while(work)
	{
		int receive = recv(sockfd, baf, LEN, 0);
    	if (receive > 0)
		{
    		printf("%s", baf);
    	}
		else if (receive == 0)
		{
			work = false;
    	}
		else
		{
			perror("recv");
		}
		if (work)
		{
			memset(baf, 0, sizeof(baf));
		}
	}
}

