//outline of sockets with this being the server and the other one file being the client.
//Did not implement any of philosopher.cpp(Kaleb's code) into it

#include "PhilosopherHeader.h"


int forks[5] = {1,1,1,1,1};
int seats[5] = {0,0,0,0,0};



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
	//we need a list to keep track of who is in what order to get the ok for the forks

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

		//me just testing to see what was sent from client
		printf("from client:  %s\n", buf);

		//send to client that its time to receive an input

		//here the server has a successful connection
		//clients are first going to ask for a seat, and be updated in the array.
		//then clients will ask to interact with the fork array.
		//they will ask if its available and if they can have it
		//then they will say im done with it and to return it

		//i think we need to receive messages from them, and switch their messages
		//have a case for seating
		//have a case for getting forks
		//have a case for returning forks
		//maybe have a case for exiting the server cleanly, but maybe thats too much work given it runs forever and is an assignment, let it crash

		//rough draft something like this? (also dont be afraid to move my old comments to the bottom/delete them if you feel fit)
		//we need to switch what the client is sending to the server, maybe we need to put this in its own loop too
		switch(buf){

			case "seating":
				//return what seat they are
			case "request":
				//ask them what they are requesting
				//if ok give them it, else put them in queue to have it later, aka centralized algo
			case "return":
				//ask them what they are returning
				//tell them ok it was returned
			default:
				//report a lack of interpretation, maybe send error?
		}

	}
}


/*
Reference from Philosopher.cpp

bool CoordinatorPermission(struct philosopher phil)
{
	//check which seat the philosopher is in
	int seat = -1;
	for(int i = 0; i < NUMPHIL; i++)
	{
		if (seats[i] == phil.ID)
			seat = i;
	}
	
	if (!(seat == -1))
	{
		//forks available initially
		//printf("before forks: 0:%d 1:%d 2:%d 3:%d 4:%d\n", forks[0],forks[1],forks[2],forks[3],forks[4]);
		//if both forks on either side of the philosopher are available,
		if ((forks[seat%5] == 1) && (forks[(seat+1)%5] == 1))
		{
			//pick up forks
			forks[seat%5] = 0;
			forks[(seat+1)%5] = 0;
			//print forks after taken
			printf("after forks: %d %d %d %d %d\n", forks[0],forks[1],forks[2],forks[3],forks[4]);
			return true;
		}
		else
			
			return false;
		
	} else {
		printf("Error in finding philosopher %d among seats.(in coordinator)", phil.ID);
		exit(5);
	}
}

int AssignSeat(struct philosopher phil)
{
	pthread_mutex_lock(&lockTwo);
	seats[tick] = phil.ID;
	phil.seat = tick;
	tick++;
	pthread_mutex_unlock(&lockTwo);
	return tick-1;
}


*/