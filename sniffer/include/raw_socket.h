#ifndef RAW_SOCKET
#define RAW_SOCKET

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
#include <stdbool.h>
#include<netinet/ip.h>
#include<netinet/tcp.h>
#include <netinet/in.h>

/*typedef struct pseudo_header
{
	u_int32_t source_address;
	u_int32_t dest_address;
	u_int8_t placeholder;
	u_int8_t protocol;
	u_int16_t tcp_length;
};*/

typedef struct ethernet_header
{
	unsigned char dest_address[6];
	unsigned char source_address[6];
	u_int16_t id_packet;
} *pether_h, ether_h;

typedef struct ip_header
{
#if defined(__LITTLE_ENDIAN_BITFIELD)
	u_int8_t len_internet_hdr:4, version:4;
#else //__BIG_ENDIAN_BITFIELD
	u_int8_t version:4, len_internet_hdr:4;
#endif
	u_int8_t service_type;
	u_int16_t total_len;
	u_int16_t id;
	u_int16_t frag_off;
	u_int8_t liveliness_time;
	u_int8_t protocol;
	u_int16_t chack;
	u_int32_t source_address;
	u_int32_t dest_address;
} *pip_h, ip_h;

typedef struct tcp_header
{
	u_int16_t source;
	u_int16_t dest;
	u_int32_t seq;
	u_int32_t ack_seq;
#if defined(__LITTLE_ENDIAN_BITFIELD)
	u_int16_t res1:4, doff:4, fin:1, syn:1,
	 rst:1, psh:1, ack:1, urg:1, ece:1, cwr:1;
#else //__BIG_ENDIAN_BITFIELD
	u_int16_t doff:4, res1:4, cwr:1, ece:1,
	 urg:1, ack:1, psh:1, rst:1, syn:1, fin:1;
#endif
	u_int16_t window;
	u_int16_t chack_sum;
	u_int16_t urg_ptr;
} *ptcp_h, tcp_h;

int prepare_socket();
unsigned short csum(unsigned short *ptr,int nbytes);
char* recv_data(int sock);
void free_ether(char* buf);
pip_h free_ip(char* buf);
void print_packet(char* buffer);
void free_tcp(char* buf, pip_h ip);
void free_data(char* buf);

#endif
