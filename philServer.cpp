// Server side C/C++ program to demonstrate Socket programming
#include "philUtils.h"


int numberOfSeats = 5;
int forks[5] = {1,1,1,1,1};
int seats[5] = {0,0,0,0,0};


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
    char *ready = "Server Ready for Commands";
    char *whichfork = "which fork               ";
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
    send(new_socket , ready , strlen(ready) , 0 );

    while(1){
	printf("Listinging...\n");
	sprintf(buffer,"%s"," ");
        valread = read( new_socket , buffer, BUFL);
	printf("[CLIENT]: %s\n",buffer );

	buf = buffer;

	if(buf.compare("request fork   ") == 0){
		printf("Requesting fork command issued\n");
		send(new_socket, whichfork, strlen(whichfork), 0 );    
		valread = read( new_socket , buffer, 2);
		printf("client requesting fork %s\n",&buffer);
	}

	else if(buf.compare("return fork     ") == 0){
		printf("return fork\n");
		send(new_socket, whichfork, strlen(whichfork), 0 );    
		valread = read( new_socket , buffer, BUFL);
		printf("returning %s\n",&buffer);

	}

	else if(buf.compare("request seating") == 0){
		printf("Client Is Requesting Seating\n");
		int seatSelection = assignSeat();
		printf("Client Seat Selection: %d\n", seatSelection);
		//char* seatStr = "  ";
		//sprintf(seatStr, "%d", seatSelection);
		sprintf(buffer,"%s","");
	}

	else {
		printf("Unkown Request\n");
	}
	
	sprintf(buffer,"%s","");
    }

    printf("Server is now exiting.\n");   
    return 0;
}