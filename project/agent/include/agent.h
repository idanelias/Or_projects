#ifndef AGENT
#define AGENT

#include "packet_analyzer/packet_analyzer.h"
#include "sniffer/raw_socket.h"
#include "server_communicator/server_commumicator.h"

//#include "../include/packet_analyzer.h"
//#include "../../sniffer/include/raw_socket.h"
//#include "../sniffer/raw_socket.h"
//#include "../packet_analyzer/packet_analyzer.h"

typedef struct node//all the packet in the same session struct
{
	packet1 pack;
	struct node *next;
} *p_node, node;

typedef struct queue//all the packet in the same session struct
{
	int size;
//	int max_size;
	p_node head;
	p_node tail;
} *p_queue, queue;

//extern p_queue que;
extern queue que;
//extern bool work;

void recv_packet(int sock);
//void secend();
void hendler_packet();
bool is_empty();
void delete_que();
void add_queue(packet1 packet);
p_node creat_node(packet1 packet);


#endif
