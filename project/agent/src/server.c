//#include "../include/packet_analyzer.h"
#include "../include/packet_analyzer/packet_analyzer.h"
//#include "../../sniffer/include/raw_socket.h"
#include "../include/sniffer/raw_socket.h"

int main()
{
	char **data;
	int s = prepare_socket();
	int s1;
	if(s == -1)
	{
		return 0;
	}

//	while(1)
	{
		s1 = operet(data,s);
		if(s1 == -1)
		{
			return 0;
		}
	}
	
}
