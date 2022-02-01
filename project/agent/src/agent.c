#include "../include/agent.h"

//int sock = 0;
//p_queue que = malloc(sizeof(queue));
queue que = {0,NULL,NULL};
//bool work= false;
//que.head = NULL;
//que.max_size = 100;
//que.size = 0;
//que.tail = NULL;

void recv_packet(int sock)//Recv packet and add her to the queue.
{
	char *data = "";
	packet1 packet;
	while(1)
	{
		printf("\n111\n");
		data = recv_data(sock);
		packet = print_packet(data);
		add_queue(packet);
		printf("\n222\n");
	}

}

void hendler_packet()
{
	while(1)
	{
		if(!is_empty() && !work)
		{
			printf("----\n\n");
//			printf("\n--hendler_packet--\n");
//			printf("\n%d",que.head->pack.dest_ip);
//			printf("\n%d",que.head->pack.source_ip);
//			printf("\n%d",que.head->pack.total_len);
//			printf("\n%d",que.head->pack.service_type);
			make_session(que.head->pack);
			printf("make_session done\n");
			delete_que();
			printf("--delete_que done--\n\n");
		}
	}
}

bool is_empty()//Checks if the queue is emptyõ
{
	return(que.head == NULL);
}

void delete_que()
{
//	p_node n;
//	n = que.head->next;
//	free(que.head->pack);
//	que.head->pack = n->pack;
//	que.head->next = n->next;

	que.head = que.head->next;
	que.size--;
	if(que.size == 0)
	{
		que.tail = NULL;
	}
}

p_node creat_node(packet1 packet)//creat new node
{
	p_node n = (p_node)malloc(sizeof(node));
	n->next = NULL;
	n->pack = packet;
	return n;
}

void add_queue(packet1 packet)
{
//	printf("~~~add_queue~~~\n");
	if(is_empty())
	{
//		printf("is empty\n");
		que.head = creat_node(packet);
//		que.head.pack.dest_ip = packet.dest_ip;
//		que.head->pack.port_dest = packet.port_dest;
//		que.head->pack.port_source = packet.port_source;
//		que.head->pack.service_type = packet.service_type;
//		que.head->pack.source_ip = packet.source_ip;
//		que.head->pack.total_len = packet.total_len;
//		que.head->next = NULL;
		que.size++;
		que.tail = que.head;
	}
	else
	{
//		printf("is not empty\n");
		que.size++;
		que.tail->next = creat_node(packet);
		que.tail = que.tail->next;
//		que.tail.next.pack.dest_ip = packet.dest_ip;
//		que.tail.next->pack.port_dest = packet.port_dest;
//		que.tail.next->pack.port_source = packet.port_source;
//		que.tail.next->pack.service_type = packet.service_type;
//		que.tail.next->pack.source_ip = packet.source_ip;
//		que.tail.next->pack.total_len = packet.total_len;
//		que.tail.next.next = NULL;
//		que.tail.pack = que.tail.next.pack;
//		que.size++;
	}
//	printf("~~~end add_queue~~~\n");
}



