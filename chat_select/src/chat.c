#include "../include/chat.h"

int str_trim_lf(char* arr, int length)// trim \n
{
    int i;
    for (i = 0; i < length; i++)
	{
	    if (arr[i] == '\n')
		{
			arr[i] = '\0';
			return 0;
		}
	}
}
