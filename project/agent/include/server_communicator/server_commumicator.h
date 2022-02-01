#ifndef SERVER_COMMUNICATOR
#define SERVER_COMMUNICATOR
//
#include "../packet_analyzer/packet_analyzer.h"
#include "../sniffer/raw_socket.h"
//#include "../include/server_commumicator.h"
//#include "../include/client.h"
#include "client.h"


// Global variables.
extern volatile sig_atomic_t flag;
extern int sockfd;

void catch_ctrl_c_and_exit(int sig);
void send_msg_handler(char* str);
int connection(int argc, char **argv);
#endif
