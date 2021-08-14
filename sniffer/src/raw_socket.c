#include "../include/raw_socket.h"

int prepare_socket ()
{
	int raw_socket = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	if(raw_socket < 0)
	{
		perror("socket");
		return raw_socket;
	}

	int one = 1;
	const int *val = &one;
	if(setsockopt(raw_socket, IPPROTO_IP, IP_HDRINCL, val, sizeof (one)) < 0)
	{
		perror("setsockopt");
		return -1;
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
	if(nbytes==1) {
		oddbyte=0;
		*((u_char*)&oddbyte)=*(u_char*)ptr;
		sum+=oddbyte;
	}

	sum = (sum>>16)+(sum & 0xffff);
	sum = sum + (sum>>16);
	answer=(short)~sum;

	return(answer);
}

char* recv_data(int sock)
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

void print_packet(char* buffer)
{
//	printf("\n\n		----------------------------------------------");
	printf("\n		________________________________________________");
	
	free_ether(buffer);

	pip_h ip = free_ip(buffer);
	if(ip->protocol == 5 || ip->protocol == 6)
	{
		free_tcp(buffer, ip);
	}
	free_data(buffer);
	
}

void free_ether(char* buf)
{
	pether_h ether = (pether_h)(buf);

	printf("\n\n	    	    -------------ETHERNET HEADER--------------");
	printf("\n		    |-Source Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X     |", ether->source_address[0],ether->source_address[1],ether->source_address[2],ether->source_address[3],ether->source_address[4],ether->source_address[5]);
	printf("\n		    |-Destination Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X|", ether->dest_address[0],ether->dest_address[1],ether->dest_address[2],ether->dest_address[3],ether->dest_address[4],ether->dest_address[5]);
	printf("\n		    |-Protocol : %d		             |", ether->id_packet);
	printf("\n	  	    ------------------------------------------\n");
}

pip_h free_ip(char* buf)
{
	pip_h ip = (pip_h)(buf + sizeof(ether_h));
	char *ip_address;
	int num;
	struct sockaddr_in dest, source;
	memset(&source, 0, sizeof(source));
	source.sin_addr.s_addr = ip->source_address;
	memset(&dest, 0, sizeof(dest));
	dest.sin_addr.s_addr = ip->dest_address;
	printf("\n		--------------------IP HEADER--------------------");
	printf("\n		|-version : %d				        |", (unsigned int)ip->version);
	printf("\n		|-Internet Header Length : %d DWORDS or %d Bytes",(unsigned int)ip->len_internet_hdr,((unsigned int)(ip->len_internet_hdr))*4);
	if((int)ip->len_internet_hdr*4 < 10)
	{
		printf("  ");
	}
	else
	{
		if((int)ip->len_internet_hdr < 10)
		{
			printf(" ");
		}
	}
	printf("|");
	printf("\n		|-Type Of Service : %d			        |",(unsigned int)ip->service_type);
	printf("\n		|-Total Length : %d Bytes		        |",ntohs(ip->total_len));
	printf("\n		|-Identification : %d			        |",ntohs(ip->id));
	printf("\n		|-Time To Live : %d			        |",(unsigned int)ip->liveliness_time);
	printf("\n		|-Protocol : ");
	if((int)ip->protocol == 5)
	{
		printf("TCP - ");
	}
	printf("%d 	   		        |",(unsigned int)ip->protocol);
	num = ntohs(ip->chack);
	printf("\n		|-Header Checksum : %d		        ",num);
	for(int i = 0; i < 5 && num > 9 && num < 1000; i++)
	{
		num = num/10;
		printf(" ");
	}
	printf("|");
	ip_address = inet_ntoa(source.sin_addr);
	while(strlen(ip_address) < 16)
	{
		strcat(ip_address, " ");
	}
	printf("\n		|-Source IP : %s		        |", ip_address);
	ip_address = inet_ntoa(dest.sin_addr);
	while(strlen(ip_address) < 16)
	{
		strcat(ip_address, " ");
	}
	printf("\n		|-Destination IP : %s	        |",ip_address);
	printf("\n		-------------------------------------------------\n");
	return ip;
}

void free_tcp(char* buf, pip_h ip)
{
	ptcp_h tcp = (ptcp_h)(buf + sizeof(tcp_h) + ((unsigned int)(ip->len_internet_hdr))*4);
	printf("\n		---------------------TCP HEADER-------------------");
	printf("\n		||-Source Port : %d				||",(unsigned int)tcp->source);
	printf("\n		||-Destination Port : %d			||",(unsigned int)tcp->dest);
	printf("\n		||-Sequence Number : %d		  	||",(unsigned int)tcp->seq);
	printf("\n		||-Acknowledge Number : %d	  	||",(unsigned int)tcp->ack_seq);
	printf("\n		||-Header Length : %d DWORDS or %d Bytes		||",(unsigned int)tcp->res1,((unsigned int)(tcp->res1))*4);
	printf("\n		|------------------------------------------------|");
	printf("\n		|-----------------------FLAGS--------------------|");
	printf("\n		||-Urgent Flags : %d				||",(unsigned int)tcp->urg);
	printf("\n		||-Acknowledgement Flags : %d			||",(unsigned int)tcp->ack);
	printf("\n		||-Push Flags : %d				||",(unsigned int)tcp->psh);
	printf("\n		||-Reset Flags : %d				||",(unsigned int)tcp->rst);
	printf("\n		||-Synchronise Flags : %d			||",(unsigned int)tcp->syn);
	printf("\n		||-Finish Flags : %d				||",(unsigned int)tcp->fin);
	printf("\n		|------------------------------------------------|");
	printf("\n		||-Window Size : %d				||",(unsigned int)tcp->window);
	printf("\n		||-Checksum : %d				||",(unsigned int)tcp->chack_sum);
	printf("\n		||-Urgent Pointer : %d				||",(unsigned int)tcp->urg_ptr);
	printf("\n		--------------------------------------------------\n");
}

void free_data(char* buf)
{
}

