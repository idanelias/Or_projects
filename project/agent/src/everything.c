#include "../include/agent.h"
int main()
{
//	char **data;
	int sock1 = prepare_socket();//Preparing to open the socket.
	int s1;
	if(sock1 == -1)
	{
		return 0;
	}
	
	pthread_t add;
	if(pthread_create(&add, NULL, (void *) recv_packet, (int*) sock1)!= 0)
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

	while(1)
	{
		if(work && num!=0)
		{
//			int number = dictionary_size;
			char *data[dictionary_size + 1];
			char **all = send_data(data);
//			printf("____________________________________________\n");
//			printf("number: %d\n",number);
//			printf("dictionary_size:%d\n",dictionary_size1);
//			for(int i = 0; i < dictionary_size1; i++)
//			{
////				printf("print dictionary[%d]\n",i-1);
//				printf("%s \n",data[i]);
//				
//			}
			
			printf("____________________________________________\n");
		}
	}

}
