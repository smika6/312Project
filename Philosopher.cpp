#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define NUMPHIL 5
#define TIMEMAX 5


pthread_mutex_t lockOne;
pthread_mutex_t lockTwo;

int forks[5] = {1,1,1,1,1};
int seats[5] = {0,0,0,0,0};
int tick = 0;

bool CoordinatorPermission(int ID)
{
	seats[tick] = ID;
	tick++;
	int seat = -1;
	for(int i = 0; i < NUMPHIL; i++)
	{
		if (seats[i] == ID)
			seat = i;
	}
	//printf("seat: %d",seat);
	if (!(seat == -1))
	{
		printf("before forks: %d %d %d %d %d\n", forks[0],forks[1],forks[2],forks[3],forks[4]);
		if ((forks[seat%5] > 0) && (forks[(seat+1)%5] > 0))
		{
			forks[seat%5] = 0;
			forks[(seat+1)%5] = 0;
			printf("after forks: %d %d %d %d %d\n", forks[0],forks[1],forks[2],forks[3],forks[4]);
			return true;
		}
		else
			
			return false;
		
	} else {
		printf("Error in finding philosopher %d among seats.(in coordinator)", ID);
		exit(5);
	}
}

int AssignSeat(int ID)
{
	pthread_mutex_lock(&lockTwo);
	seats[tick] = ID;
	tick++;
	pthread_mutex_unlock(&lockTwo);
	return tick-1;
}

using namespace std;

void *philosopher(void *input)
{
	int ID = *(int *)input;
	int seat = AssignSeat(ID);
	bool permission;
	for (int i = 0; i <NUMPHIL; i++)
	{
		if (seats[i] == ID)
		{
			seat = i;
		}
	}
	if (seat == -1)
	{
		printf("error in finding philospher %d among seats. (in philosopher)", ID);
		exit(4);
	}	
	int thinkTime = rand()%TIMEMAX +1;
	int eatTime = rand()%TIMEMAX +1;
	sleep(1);
	while(true)
	{
		//printf("philosopher %d is thinking\n",ID);
		sleep(thinkTime);
		pthread_mutex_lock(&lockOne);
		if (CoordinatorPermission(ID))
		{
			//printf("philosopher %d is done thinking\n", ID);
			printf("philosopher %d is eating\n", ID);
			sleep(eatTime);
			//printf("philosopher %d is done eating\n",ID);
			forks[seat%5] = 1;
			forks[(seat+1)%5] = 1;
		} else {
			printf("philosopher %d is unable to eat yet, continuing to think\n", ID);
		}
		pthread_mutex_unlock(&lockOne);
	}
}


int main(int argc,char *argv[])
{
	int error;
	//5 threads per assignment
	pthread_t thread[NUMPHIL];
	int ID;
	for (int i = 0; i < NUMPHIL; i++)
	{
		ID = rand()%1000 + 1;
		printf("Id %d = %d\n", i, ID);
		error = pthread_create(&thread[i], NULL, &philosopher, (void* ) &ID);
		sleep(0.5);
	}
	
	for (int i = 0; i < NUMPHIL ; i++)					//joining threads
	{
		pthread_join(thread[i],NULL);
	}
	//philosopher();
	
	return 0;
}
