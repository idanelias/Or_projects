#ifndef CLIENT
#define CLIENT

// Global variables.
extern volatile sig_atomic_t flag;
extern int sockfd;
extern char name[32];
extern char room[3];

void catch_ctrl_c_and_exit(int sig);
void send_msg_handler();
void recv_msg_handler();

#endif
