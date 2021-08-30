#include "../include/raw_socket.h"

int main()
{
	char *data = "";
	while(1)
	{
		int s = prepare_socket();
		if(s == -1)
		{
			return 0;
		}
		data = recv_data(s);
		print_packet(data);
	}
	
}
