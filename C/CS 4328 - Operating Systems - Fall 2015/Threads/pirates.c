#include <stdio.h>
#include <math.h> // for the ceil() function
#include <pthread.h>

#define NUMTHREADS 4
#define CAVECAP 1


//Create the function prototype for the consumer(10%) 
//As well as, the consumer(15%)
void *consumeTen();
void *consumeFifteen();

/*
	Create a struct to manage data for each thread:
		- Each thread will have it's own 'name'
		- Each thread will have it's own int to track the # of pearls taken
		- Each thread will have it's own pointer to the 'pearls' variable. 
*/
struct data //cannot initialize structs in c, remember that. 
{
	pthread_t threadID;
	char name;
	int pearlsTaken;
	int *pearls;
};


//GLOBAL VARIABLES 
int pearls = 1000; // Initialize the "pearls" to 1000.
int occupied = 0;
pthread_mutex_t mutex; //create the mutex (only 1 thread can access at a time)
pthread_cond_t full_cond; // create a condition for "full"
pthread_cond_t empty_cond; // create a condition for "empty"
struct data threadData[NUMTHREADS]; //Create 4 structs of thread data (one for each thread)


int main()
{ 
	int i, j;
	//pthread_t threadID[NUMTHREADS];

	threadData[0].name = 'A';
	threadData[0].pearlsTaken = 0;
	threadData[1].name = 'B';
	threadData[1].pearlsTaken = 0;
	threadData[2].name = 'C';
	threadData[2].pearlsTaken = 0;
	threadData[3].name = 'D';
	threadData[3].pearlsTaken = 0;


	pthread_setconcurrency(NUMTHREADS); //Allow 4 threads to run concurrently

	//(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
	//Could be placed inside a for loop, that runs twice. 
	pthread_create(&threadData[0].threadID, NULL, (void *(*)(void *))consumeTen, &threadData[0]);
	pthread_create(&threadData[1].threadID, NULL, (void *(*)(void *))consumeTen, &threadData[1]);
	pthread_create(&threadData[2].threadID, NULL, (void *(*)(void *))consumeFifteen, &threadData[2]);
	pthread_create(&threadData[3].threadID, NULL, (void *(*)(void *))consumeFifteen, &threadData[3]);
	
	pthread_exit(0);
}

void *consumeTen()
{
	double pearlsToTake = 0;
	//Do stuff.
	while(pearls != 0)
	{
		pthread_mutex_lock(&mutex);
		occupied = 1;
		if(occupied == CAVECAP)
		{
			printf("There is already a pirate in the cave, this thread cannot enter \n");
			pthread_cond_wait(&full_cond, &mutex);
		}
		else
		{
			//Important code goes here. 
			pearlsToTake = (.10) * pearls;
			pearlsToTake = ceil(pearlsToTake); // round up if not a whole number. 

			printf("Pirate %c took %d pearls from the chest \n", threadData->name, pearlsToTake);

			pearls -= pearlsToTake;
			threadData->pearlsTaken += pearlsToTake;
		}
		occupied = 0;
		pthread_cond_broadcast(&full_cond);
		pthread_mutex_unlock(&mutex);

	}
}

void *consumeFifteen()
{
	double pearlsToTake = 0;
	//Do stuff.
	while(pearls != 0)
	{
		pthread_mutex_lock(&mutex);
		occupied = 1;
		if(occupied == CAVECAP)
		{
			printf("There is already a pirate in the cave,sdasd this thread cannot enter \n");
			pthread_cond_wait(&full_cond, &mutex);
		}
		else
		{
			//Important code goes here. 
			pearlsToTake = (.15) * pearls;
			pearlsToTake = ceil(pearlsToTake); // round up if not a whole number. 

			printf("Pirate %c took %d pearls from the chest \n", threadData->name, pearlsToTake);

			pearls -= pearlsToTake;
			threadData->pearlsTaken += pearlsToTake;
		}
		occupied = 0;
		pthread_cond_broadcast(&full_cond);
		pthread_mutex_unlock(&mutex);
	}  
}
