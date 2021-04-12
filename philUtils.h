#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <sstream>  // for string streams
#include <iostream>
#include <time.h>
#include <signal.h>

#define SERVERPORT 31203
#define SERVERIP "199.17.28.75"
#define SERVERNAME "ahscentos"
#define BUFL 1024

#define NUMPHIL 5
#define TIMEMAX 5

using namespace std;

struct philosopher{
	int eatTime;
	int thinkTime;
	int seat;
};

#define FORK1 "001"
#define FORK2 "002"
#define FORK3 "003"
#define FORK4 "004"
#define FORK5 "005"

#define SEAT1 "010"
#define SEAT2 "020"
#define SEAT3 "030"
#define SEAT4 "040"
#define SEAT5 "050"

#define CONNECTING    "000"
#define ASSIGNSEATING "100"
#define REQUESTFORK   "200"
#define RETURNFORK    "300"
#define LEAVEWAITLIST "400"
