// Client side C/C++ program to demonstrate Socket programming
#include "philUtils.h"

char buffer[BUFL] = {0};
int sock = 0, valread;
//ostringstream stringconverter;
//char forkStr[5+sizeof(char)];

int requestSeating(){
	//send to server 'seating'
	//be updated in the servers array
	//be returned the index/location in the ring
	//return that location for client reference

	printf("Requesting Seating.\n");
	send(sock, ASSIGNSEATING, strlen(ASSIGNSEATING), 0);

	//read in the seat
	//assign it/return it
}

int requestFork(int forkIndex){
	//send to server 'request'
	//get back an ok for which fork
	//send the server the desired fork
	//sit around looking for that ok you have the fork 

	printf("Requesting Fork: %d\n", forkIndex);
	send(sock, REQUESTFORK, strlen(REQUESTFORK), 0); 
	
	valread = read( sock , buffer, BUFL);    
	printf("Server says: %s\n",buffer );

	//sprintf(forkStr,"%d",forkIndex);
	//send(sock, forkStr, strlen(forkStr), 0);

	return 0;
}

int returnFork(int forkIndex){
	//send to server 'return'
	//get back an ok for which fork
	//send the server the fork for return
	//sit around looking for that ok you no longer have the fork

	printf("Returning Fork: %d\n", forkIndex);
	send(sock, RETURNFORK, strlen(RETURNFORK), 0); 
		
	valread = read( sock , buffer, BUFL);    
	printf("%s\n",buffer );	
	
	//sprintf(forkStr,"%d",forkIndex);
	//send(sock, forkStr, strlen(forkStr), 0);

	return 0;
}

void eat(struct philosopher phil){

	phil.eatTime = rand()%TIMEMAX + 1;
	printf("Phil at seat %d is Eating for %d\n", phil.seat, phil.eatTime);
	sleep(phil.eatTime);
}

void think(struct philosopher phil){
	
	phil.thinkTime = rand()%TIMEMAX + 1;	
	printf("Phil at seat %d is Thinking for %d\n", phil.seat, phil.thinkTime);
	sleep(phil.thinkTime);
}

int main(int argc, char const *argv[])
{
    struct philosopher phil;
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVERPORT);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, SERVERIP, &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock , CONNECTING, strlen(CONNECTING) , 0 );
    printf("Attempting to Connect\n");
    valread = read( sock , buffer, BUFL);
    printf("%s\n",buffer );

    sprintf(buffer,"%s","");
    phil.seat = requestSeating();
    
    while(1 && phil.seat != -1) {

        sprintf(buffer,"%s","");
	requestFork(phil.seat%5);

        sprintf(buffer,"%s","");
	requestFork((phil.seat+1)%5);
	//if it takes too long avoid deadlock by returning fork
		//returnFork(phil.seat%5);
		
	//if we have both forks then eat and return them
	eat(phil);
	
        sprintf(buffer,"%s","");
	returnFork(phil.seat%5);
	 
        sprintf(buffer,"%s","");
	returnFork((phil.seat+1)%5);

	//always think after we eat or do not eat
	think(phil);
    }
    

    printf("Client is now exiting.\n");
    return 0;
}
