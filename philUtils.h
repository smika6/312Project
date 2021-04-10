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