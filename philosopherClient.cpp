//outline of sockets in a client
//did not implement any of philosopher.cpp(Kaleb's code) into it

#include "PhilosopherHeader.h"

int requestSeating(){
	//send to server 'seating'
	//be updated in the servers array
	//be returned the index/location in the ring
	//return that location for client reference
}

int requestFork(){
	//send to server 'request'
	//get back an ok for which fork
	//send the server the desired fork
	//sit around looking for that ok you have the fork 
}

int returnFork(){
	//send to server 'return'
	//get back an ok for which fork
	//send the server the fork for return
	//sit around looking for that ok you no longer have the fork
}

void eat(struct philosopher phil){

	phil.eatTime = rand()%TIMEMAX + 1;
	sleep(phil.eatTime);
}

void think(struct philosopher phil){
	
	phil.thinkTime = rand()%TIMEMAX + 1;
	sleep(phil.thinkTime);
}


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

	// we need some int/bool to determine if both forks were grabed and we should eat, or if we didnt get the forks we wanted and will think only

	//get an ok from server that its time to send messages

	//request to be seated
	int seat = requestSeating();

	while(1){ //loop eating and thinking

		//check if fork 1 is available
			requestFork(seat%5);
		
		//check if fork 2 is available
			requestFork((seat+1)%5);
		//else if it takes too long avoid deadlock by returning fork
			returnFork(seat%5);
		
		//if we have both forks then eat and return them
			eat();
			returnFork(seat%5);
			returnFork((seat+1)%5);

		//always think after we eat or do not eat
		think();
	}

	printf("Client is exiting.\n");
	return 0;

}

/*
Reference to Philosopher.cpp
void *philosopherMethod(void *input)
{
	struct philosopher phil = *(struct philosopher *)input;
	
	phil.seat = AssignSeat(phil);
	printf("philosopher: %d, seat: %d\n",phil.ID, phil.seat);
	sleep(1);
	printf("philosopher %d is thinking\n",phil.ID);
	while(true)
	{
		sleep(phil.thinkTime);
		pthread_mutex_lock(&lockOne);
		if (CoordinatorPermission(phil))
		{	
			printf("philosopher %d is eating\n", phil.ID);
			sleep(phil.eatTime);
			printf("philosopher %d is done eating\n",phil.ID);
			printf("philosopher %d is thinking\n",phil.ID);
			forks[phil.seat%5] = 1;
			forks[(phil.seat+1)%5] = 1;
		} 
		pthread_mutex_unlock(&lockOne);
	}
}
*/
