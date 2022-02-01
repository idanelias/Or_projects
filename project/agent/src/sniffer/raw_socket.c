#include "../../include/sniffer/raw_socket.h"

int prepare_socket()
{
	int raw_socket = socket(AF_PACKET, SOCK_RAW,htons(ETH_P_IP));
	if(raw_socket < 0)
	{
		perror("socket");
		return raw_socket;
	}
	return raw_socket;
}

unsigned short csum(unsigned short *ptr,int nbytes)
{
	register long sum;
	unsigned short oddbyte;
	register short answer;

	sum=0;
	while(nbytes>1) {
		sum+=*ptr++;
		nbytes-=2;
	}
	if(nbytes == 1) {
		oddbyte = 0;
		*((u_char*)&oddbyte)=*(u_char*)ptr;
		sum+=oddbyte;
	}

	sum = (sum>>16)+(sum & 0xffff);
	sum = sum + (sum>>16);
	answer=(short)~sum;

	return(answer);
}

char* recv_data(int sock)//recv data
{
	unsigned char *buffer = (unsigned char *) malloc(65536); //to receive data
	memset(buffer,0,65536);
	struct sockaddr saddr;
	int saddr_len = sizeof(saddr);

	//Receive a network packet and copy in to buffer
	if(recvfrom(sock,buffer,65536,0,&saddr,(socklen_t *)&saddr_len) < 0)
	{
		perror("recvfrom\n");
		return "";
	}
	
	return buffer;
}

packet1 print_packet(char* buffer)//print the packet
{
	pether_h ether = free_ether(buffer);

	pip_h ip = free_ip(buffer);

	if(ip->protocol == 5 || ip->protocol == 6)
	{
		free_tcp(buffer, ip);
	}

	if(ip->protocol == 8)
	{
		free_udp(buffer, ip);
	}

	packet1 packet;
	
	packet.dest_ip = ip->dest_address;
	packet.source_ip = ip->source_address;
	packet.service_type = ip->service_type;
	packet.total_len = ip->total_len;
	p_port port = (p_port)(buffer + ((unsigned int)(ip->len_internet_hdr))*4);
	packet.port_source = port->port;
	port = (p_port)(buffer + sizeof(port1) + ((unsigned int)(ip->len_internet_hdr))*4);
	packet.port_dest = port->port;
	return packet;
}

pether_h free_ether(char* buf) //save in variable and print the ethernet header
{
	pether_h ether = (pether_h)(buf);
	return ether;
}

pip_h free_ip(char* buf) //save in variable and print the ip header
{
	pip_h ip = (pip_h)(buf + sizeof(ether_h));
	char *ip_address;
	int num;
	struct sockaddr_in dest, source;
	memset(&source, 0, sizeof(source));
	source.sin_addr.s_addr = ip->source_address;
	memset(&dest, 0, sizeof(dest));
	dest.sin_addr.s_addr = ip->dest_address;
	return ip;
}

void free_tcp(char* buf, pip_h ip) //save in variable and print the tcp header
{
	ptcp_h tcp = (ptcp_h)(buf + sizeof(tcp_h) + ((unsigned int)(ip->len_internet_hdr))*4);
}

void free_udp(char* buf, pip_h ip)//save in variable and print the udp header
{
	pudp_h udp = (pudp_h)(buf + ip->len_internet_hdr*4 + sizeof(ether_h));
	printf("\n		---------------------UDP HEADER-------------------");
	printf("\n		||-Source Port : %d				||",(unsigned int)udp->source);
	printf("\n		||-Destination Port : %d			||",(unsigned int)udp->dest);
	printf("\n		||-UDP Length : %d				||",udp->len);
	printf("\n		||-UDP Chacksum : %d			||",udp->chack);
	printf("\n		--------------------------------------------------\n");
}

void free_data(char* buf, pip_h ip)//save in variable and print the data
{
	unsigned char * data = (buf + ((unsigned int)(ip->len_internet_hdr))*4 + sizeof(ether_h) + sizeof(tcp_h));
	unsigned int remaining_data = strlen(buf) - (((unsigned int)(ip->len_internet_hdr))*4 + sizeof(ether_h) + sizeof(tcp_h));

	printf("\n");

	for(int i=0;i< 0 - remaining_data;i++)
	{
		if(i!=0 && i%16==0)
			printf("\n");
		printf(" %.2X ",data[i]);
	}
	
}

