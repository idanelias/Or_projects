#ifndef chat
#define chat

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

#define MAX_CLIENTS 100
#define LEN 2048

int str_trim_lf(char* arr, int length);// trim \n

#endif
