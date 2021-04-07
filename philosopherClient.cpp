//outline of sockets in a client
//did not implement any of philosopher.cpp(Kaleb's code) into it

#include "PhilosopherHeader.h"
using namespace std;


int main(int argc, char* argv[])
{
	
	int err;
	int cSocket;
	struct sockaddr_in sAddr;
	struct sockaddr_in cAddr;
	int cSocLen;
	char buf[BUFL];
	size_t found;

	memset(&cAddr, 0, sizeof(struct sockaddr_in));
	cAddr.sin_family = AF_INET;
	cAddr.sin_port = htons(SERVERPORT);
	cAddr.sin_addr.s_addr = inet_addr(SERVERIP);

	cSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (cSocket == -1)
	{
		perror("socClient: socket creation failed");
		exit(1);
	}

	err = connect(cSocket, (struct sockaddr*)&cAddr, sizeof(struct sockaddr_in));
	if (err == -1)
	{
		perror("socClient: connect failed");
		exit(2);
	}

	err = send(cSocket, "Connection made!\n", 17, 0);

	printf("Client is exiting.\n");
	return 0;

}
