//outline of sockets with this being the server and the other one file being the client.
//Did not implement any of philosopher.cpp(Kaleb's code) into it

#include "PhilosopherHeader.h"
using namespace std;

int main()
{
	//Variables
	int error;
	int exitCode = 0;
	pid_t cpid;
	int sSocket;
	int cSocket;
	struct sockaddr_in sAddr;
	struct sockaddr_in cAddr;
	unsigned int cSocLen;
	char buf[BUFL];
	//char param[BUFL];
	char sSocketPass[BUFL];
	char cSocketPass[BUFL];


	//socket creation
	printf("Attempting to create socket.\n");
	sSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (sSocket == -1)
	{
		perror("SocServer: socket creation failed");
		exit(2);
	}
	printf("Socket creation successful.\n");


	// server address
	memset(&sAddr, 0, sizeof(struct sockaddr_in));
	sAddr.sin_family = AF_INET;
	sAddr.sin_port = htons(SERVERPORT);
	//sAddr.sin_port = 0;
	sAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//bind socket to server
	printf("Server: attempting to bind.\n");
	error = bind(sSocket, (struct sockaddr*)&sAddr, sizeof(struct sockaddr_in));
	if (error == -1)
	{
		perror("bind address to socket failed");
		exit(3);
	}
	printf("Server: bind Successful.\n");

	//listen 
	printf("Server: attempting Listen.\n");
	error = listen(sSocket, 5);
	if (error == -1)
	{
		perror("Listen failed.");
		exit(4);
	}
	printf("Server: listen successful.\n");

	//add condition to check for how many attempting to connect
	while (1)
	{

		printf("Server: Waiting for client connection to attempt to accept.\n");
		cSocket = accept(sSocket, (struct sockaddr*)&cAddr, &cSocLen);
		if (cSocket == -1)
		{
			perror("Accept failed.");
			exit(5);
		}
		printf("Server: connection received and accept successful.\n");
		sprintf(sSocketPass, "%d", sSocket);
		sprintf(cSocketPass, "%d", cSocket);

		error = recv(cSocket, cSocketPass, BUFL, 0);
		if (error == -1)
		{
			printf("socServer: read failed");
			exit(6);
		}
		printf("socServer:  %s\n", cSocketPass);
	}
}


