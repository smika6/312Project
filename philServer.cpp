// Server side C/C++ program to demonstrate Socket programming
#include "philUtils.h"


const int numberOfSeats = 5;

//this keeps track of fork locations,
//here i think 1 means fork present, 0 means its taken/missing
int forks[numberOfSeats] = {1,1,1,1,1};

//0 is an empty seat and 1 is taken
int seats[numberOfSeats] = {0,0,0,0,0};

//this will keep track of whos in line to receive a specific fork
int waitlist[numberOfSeats][numberOfSeats];


int assignSeat()
{
	for(int i = 0; i < numberOfSeats; i++){
		if(seats[i] == 0){
			seats[i] == 1;
			return i;
		}
	}
	return -1;
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFL] = {0};
    string buf;
       
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
       
    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( SERVERPORT );
       
    // Forcefully attaching socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Server Waiting for Connection...\n");
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    printf("Successful Connection Made\n");
    valread = read( new_socket , buffer, BUFL);
    send(new_socket , CONNECTING , strlen(ready) , 0 );

    while(1){
	printf("Listinging...\n");
	sprintf(buffer,"%s"," ");
        valread = read( new_socket , buffer, BUFL);
	printf("[CLIENT]: %s\n",buffer );

	buf = buffer;

	if(buf.compare(REQUESTFORK) == 0){
		printf("Requesting fork command issued\n");
		send(new_socket, WHICHFORK, strlen(whichfork), 0 );    
		valread = read( new_socket , buffer, BUFL);
		printf("client requesting fork %s\n",&buffer);
	}

	else if(buf.compare(RETURNFORK) == 0){
		printf("Return fork command issued\n");
		send(new_socket, WHICHFORK, strlen(whichfork), 0 );    
		valread = read( new_socket , buffer, BUFL);
		printf("returning %s\n",&buffer);

	}

	else if(buf.compare(ASSIGNSEATING) == 0){
		printf("Client Is Requesting Seating\n");
		int seatSelection = assignSeat();
		printf("Client Seat Selection: %d\n", seatSelection);
		//char* seatStr = "  ";
		//sprintf(seatStr, "%d", seatSelection);
	}
	    
	else if(buf.compare(LEAVEWAITLIST) == 0){
	}

	else {
		printf("Unkown Request\n");
	}
    }

    printf("Server is now exiting.\n");   
    return 0;
}
