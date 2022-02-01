#include "../../include/packet_analyzer/packet_analyzer.h"

//pthread secend: Resource temporarily unavailable
//
//socket: Too many open files
//
//pthread print_analyze_packet: Resource temporarily unavailable

bool work = false;//If you are supposed to send the information
int num = 0;//Number of packets thet arrived in one second
int len = 0;//Total length of all the packetes thet arrived in one second
int dictionary_size = 0;//The size of thr dictionary
int dictionary_size1 = 0;
p_dictionary dictionary;//Contains all the different packetes that went through in a second
//dictionary = (p_dictionary)malloc(sizeof(dictionary1)*dictionary_size);
int sock = 0;//The socket

void print_analyze_packet()//recv the packet, print and send het to make session.
{
	char *data = "";
	packet1 packet;
	while(1)
	{
		data = recv_data(sock);
		packet = print_packet(data);
//		printf("3\n");
//		printf("%d 1",packet.dest_ip);
//		printf("\n%d 2",packet.source_ip);
//		printf("\n%d 3",packet.total_len);
//		printf("\n%d 4",packet.service_type);
		make_session(packet);
	}
	
}

void make_session(packet1 packet)//make session
{
	printf("__start make_session__\n");
	session_key key;
	if(packet.dest_ip < packet.source_ip)
	{
		key.ip[0] = packet.dest_ip;
		key.ip[1] = packet.source_ip;
	}
	else
	{
		key.ip[1] = packet.dest_ip;
		key.ip[0] = packet.source_ip;
	}
	struct sockaddr_in ip;

	memset(&ip, 0, sizeof(ip));
	ip.sin_addr.s_addr = key.ip[0];
//	printf("ip1: %s\n",inet_ntoa(ip.sin_addr));

	memset(&ip, 0, sizeof(ip));
	ip.sin_addr.s_addr = key.ip[1];
//	printf("ip2: %s\n",inet_ntoa(ip.sin_addr));
	
	if(packet.port_dest < packet.port_source)
	{
		key.port[0] = packet.port_dest;
		key.port[1] = packet.port_source;
	}
	else
	{
		key.port[1] = packet.port_dest;
		key.port[0] = packet.port_source;
	}
	
//	printf("port1: %d\nport2: %d\n",key.port[0],key.port[1]);
//	printf("total len: %d\n",packet.total_len);
//	printf("service type: %d\n\n",packet.service_type);
	
	len += packet.total_len;
	num++;
	
	int index = find_in_dictionary(key);
//	int index1 = find_in_dictionary(key);
//	printf("\nindex: %d\ndictionary_size: %d\n",index,dictionary_size);
	
	if(dictionary_size == 0)
	{
		dictionary = (p_dictionary)malloc(sizeof(dictionary1)*dictionary_size);
	}
	if(index == (-1) || dictionary_size == 0/*|| index1 == (-1)*/)
	{
		
		printf("did not find\n\n");
		add_to_dictionary(key, packet);
	}
	else
	{
		printf("find in index %d\n\n",index);
		dictionary[index].s.num_of_packets++;
		dictionary[index].s.bps += packet.total_len;
		dictionary[index].s.avg_psize = dictionary[index].s.bps/dictionary[index].s.num_of_packets;
	}
	printf("__end make__\n");
}

int find_in_dictionary(session_key key)//Search for the packet in the dictionary.
{
//	printf("---dictionary_size: %d\n",dictionary_size);
//	printf("key ------- ip1 = %d ,ip2 = %d ,port1 = %d ,port2=%d\n",key.ip[0],key.ip[1],key.port[0],key.port[1]);
	for (int j = 0; j < dictionary_size; j++)//////////////////////////////////////////
	{
//		printf("ip1 = %d ,ip2 = %d ,port1 = %d ,port2=%d\n",dictionary[j].key.ip[0],dictionary[j].key.ip[1],dictionary[j].key.port[0],dictionary[j].key.port[1]);
		if(key.ip[0] == dictionary[j].key.ip[0] && key.ip[1] == dictionary[j].key.ip[1] && key.port[0] == dictionary[j].key.port[0] && key.port[1] == dictionary[j].key.port[1])//return the index
		{
//			printf("%d\n%d\n",dictionary[j].s.num_of_packets,j);
			return j;
		}
	}
	return -1;
}

void add_to_dictionary(session_key key,packet1 packet)//Add the packet to the dictionary.
{
	printf("\nrealloc - 1\n");
	dictionary = (p_dictionary)realloc(dictionary,(dictionary_size+1)*(sizeof(dictionary1)));
	session s;
//	if(packet.dest_ip < packet.source_ip)
//	{
//		s.ip[0] = packet.dest_ip;
//		s.ip[1] = packet.source_ip;
//	}
//	else
//	{
//		s.ip[1] = packet.dest_ip;
//		s.ip[0] = packet.source_ip;
//	}
	s.ip[0] = key.ip[0];
	s.ip[1] = key.ip[1];
	s.port[0] = key.port[0];
	s.port[1] = key.port[1];
//	if(packet.port_dest < packet.port_source)
//	{
//		s.ip[0] = packet.port_dest;
//		s.ip[1] = packet.port_source;
//	}
//	else
//	{
//		s.ip[1] = packet.port_dest;
//		s.ip[0] = packet.port_source;
//	}
	s.service_type = packet.service_type;
	s.num_of_packets = 1;
	s.bps = packet.total_len;
	
	dictionary[dictionary_size].s = s;
	dictionary[dictionary_size].key = key;
	dictionary_size++;
//	printf("dictionary_size = %d\n",dictionary_size);
//	printf("done add_to_dictionary\n");
}

/* char* str_rev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}
*/

//int operet(char **all, int s1)
//{
////	pthread_t sec;
////	if(pthread_create(&sec, NULL, (void *) secend,(char**)all) != 0)
////	{
////		perror("pthread secend");
////		return 0;
////	}
//	while(1)
//	{
//		if(work)
//		{
//			send_data(all);
//		}
//	}
//	return dictionary_size;
//}

char* send_global()//Sends the information about everything that happened from the last reset as a string.
{
	char* st = (char *)malloc(sizeof(char)*50);
	strcpy(st,"g");
//	char st1[200]={};///////////////
//	strcpy(st1," ");//////////////////////
//	strcat(st,st1);
//	sprintf(st1, "%s %d", st,num);
//	strcpy(st,st1);
	sprintf(st, "%s %d", st,num);
//	int num1 = sizeof(char)*(strlen(st1)+ 23);
//	st = (char *)realloc(st,num1);
	float n = len/(num);
	sprintf(st, "%s %f %d",st,n,len);
//	printf("%s\n",st);
	return st;
}

char* send_session(session s)//Sends the information about the session that the function received as a string.
{
	char* st = (char *)malloc(sizeof(char)*200);
	strcpy(st,"s");
	sprintf(st, "%s ip1:%d ip2:%d port1:%d port2:%d service_type:%d bps:%d avg_psize:%d num_of_packets:%d",st,s.ip[0],s.ip[1],s.port[0],s.port[1],s.service_type,s.bps,s.avg_psize,s.num_of_packets);
	return st;
}

void secend()//send the datd to the server_communicator
{
	while(1)
	{
		work = false;
		sleep(1);
		work = true;
		sleep(1);
	}
}


char **send_data(char **all)//Make the string on the dictionary.
{
//	printf("\n------------------------------------------------------------\nstart send_data\n");
//	char *all[dictionary_size+1];

	all[0] = send_global();
//	*all=(char *)malloc(sizeof(char)*300);
//	char *st = send_global();
//	all[0]=(char *)malloc(sizeof(char)*strlen(st));
//	sprintf(*all, "%s", send_global());
//	sprintf(all[0], "%s", st);
//	printf("dictionary_size = %d\n",dictionary_size);
	for(int i = 0; i <= dictionary_size; i++)
	{
		printf("%d\n",i);
//		*(all + i)=(char *)malloc(sizeof(char)*300);
//		char *st1 = send_session(dictionary[i].s);
//		printf("%s\n %ld\n",st1,strlen(st1));
//		all[i+1]=(char *)malloc(sizeof(char)*strlen(st1));
		all[i+1] = send_session(dictionary[i].s);
//		strcpy(all[i+1], st1);
//		strcpy(all[i+1], send_session(dictionary[i].s));
//		printf("%s \n",all[i+1]);///////////////////////////////////////////////
	}
	printf("dictionary_size = %d\n\n",dictionary_size);
	int size_of_dictionary = dictionary_size;
	printf("dictionary_size = %d\n\n",size_of_dictionary);
	for(int i = 0; i <= size_of_dictionary; i++)
	{
		printf("print dictionary[%d]\n",i-1);
		printf("%s \n",all[i]);
	}
	num = 0;
	len = 0;
//	for(int i = 0; i < dictionary_size + 1; i++)
// 	{
//		printf("\t\t\t\t\t %s \n",all[i+1]);
//	}

	printf("\n00000\n");
	if(dictionary_size>0)
	{
		printf("\nrealloc - 2\n");
		free(dictionary);
//		dictionary = (p_dictionary)realloc(dictionary,(1*sizeof(dictionary1)));
//		free(dictionary);
//		p_dictionary dictionary;
	}
	dictionary_size1 = dictionary_size;
	dictionary_size = 0;
//	printf("end send_data\n------------------------------------------------------------\n");
	return all;
}

