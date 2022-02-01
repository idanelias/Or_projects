#ifndef PACKET_ANALYZER
#define PACKET_ANALYZER

//#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdbool.h>
#include "../sniffer/raw_socket.h"

typedef struct session//all the packet in the same session struct
{
	u_int32_t ip[2];
	u_int16_t port[2];
	u_int8_t service_type;
	u_int32_t bps;//byte per secend
	u_int16_t avg_psize;
	u_int32_t num_of_packets;
} *p_session, session;

typedef struct session_key//all the packet in the same session struct
{
	u_int32_t ip[2];
	u_int16_t port[2];
} *p_session_key, session_key;

typedef struct dictionary//packet struct
{
	session s;
	session_key key;
} *p_dictionary, dictionary1;

typedef struct global_data_per_secend//packet struct
{
	u_int32_t bps;//byte per secend
	u_int16_t avg_psize;
	u_int32_t num_of_packets;
} *p_gdps, gdps;

extern int num;//number of packets thet arrived in one second
extern int len;//Total length of all the packetes thet arrived in one second
extern int sock;//The socket
extern bool work;//If you are supposed to send the information
extern int dictionary_size;//The size of thr dictionary
extern int dictionary_size1;
extern p_dictionary dictionary;//Contains all the different packetes that went through in a second

void print_analyze_packet();//recv the packet, print and send het to make session.
void make_session(packet1 packet);//make session
int find_in_dictionary(session_key key);//Search for the packet in the dictionary.
void add_to_dictionary(session_key key,packet1 packet);//Add the packet to the dictionary.
int operet(char **all, int s1);
char* send_global();//Sends the information about everything that happened from the last reset as a string.
void secend();//send the datd to the server_communicator
char *send_session(session s);//Sends the information about the session that the function received as a string.
char** send_data(char **all);//Make the string on the dictionary.
//char* str_rev(char *str);


#endif
