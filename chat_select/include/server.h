#ifndef SERVER
#define SERVER

#define LOGFILE "server.log"
#define LOG_TIME_FORMAT "%Y-%m-%d %H:%M:%S"
#define MAX_CLIENTS 100
#define LEN 2048

static _Atomic unsigned int cli_count = 0;
static int uid = 10;
extern int listenfd;
extern int port;
extern char *ip;
extern int option;
extern struct sockaddr_in serv_addr;
extern bool work;

//Client structure
typedef struct
{
	struct sockaddr_in address;
	int sockfd;
	int uid;
	char room;
	char name[32];
} client_t;

extern client_t *clients[MAX_CLIENTS];

//extern pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;
extern pthread_mutex_t clients_mutex;

void get_timestamp(char *dt);
void print_log(char *msg);
void printclient(struct sockaddr_in addr);
void queue_add(client_t *cl);
void queue_remove(int uid);
void sendinfo(char *s, int uid, char room);
int handle_client(void *arg);
int prepar_socket();

#endif
