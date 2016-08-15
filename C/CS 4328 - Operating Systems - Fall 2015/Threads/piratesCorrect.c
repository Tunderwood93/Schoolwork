#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <stdio.h>

/*
	DEFINES
*/
#define CAPACITY 1 // Number of space in the "chest", kind of useless in reality. 
#define TIMESTORUN 100 // Number of times the for loops in the thread functions run. 
#define CHESTSIZE 5 // Size of my array, could probably be changed to 1. 

/*
	FUNCTION PROTOTYPES
*/
void *producer(); // Function prototype for the producer thread. 
void *consumeTenA(); // Function prototype for a 10% consumer (pirate a) thread.
void *consumeTenB(); // Function prototype for a 10% consumer (pirate b) thread.
void *consumeFifteenC(); // Function prototype for a 15% consumer (pirate c) thread.
void *consumeFifteenD(); // Function prototype for a 15% consumer (pirate d) thread.
void resultsAndTerminate(); // Function prototype that displays the amount of pearls taken by each thread & then exits the program. 

/*
	STRUCT
*/
struct Data
{
	int item[CHESTSIZE]; //Array that contains the pearls
	int size; // Int that keeps track if there's an item in the chest
};

/*
	GLOBAL VARIABLES
*/
int pearls = 1000; // Start the chest at 1000 pearls
pthread_mutex_t mutex; // Mutual exclusion lock
pthread_cond_t full_cond; // Mutual exclusion lock condition for a full condition.
pthread_cond_t empty_cond; // Mutual exclusion lock condition for an empty condition.
struct Data chest; // Create the struct object. 

// Variables to track how many pearls each thread took. 
int pirateATook = 0;
int pirateBTook = 0;
int pirateCTook = 0;
int pirateDTook = 0;



int main()
{
	int i; 
	pthread_t threadID; // Variable for the threadID's 

	// Initialize the struct. 
	for(i = 0; i < CHESTSIZE; i++)
	{
		chest.item[i] = -1;
		chest.size = 0;
	}

	pthread_setconcurrency(5); // 1 producer thread + 4 consumer threads = 5 total threads running concurrently 

	// Create the threads & we're off. 
	pthread_create(&threadID, NULL, (void *(*)(void *))producer, NULL  );
  	pthread_create(&threadID, NULL, (void *(*)(void *))consumeTenA, NULL );
  	pthread_create(&threadID, NULL, (void *(*)(void *))consumeTenB, NULL );
  	pthread_create(&threadID, NULL, (void *(*)(void *))consumeFifteenC, NULL );
  	pthread_create(&threadID, NULL, (void *(*)(void *))consumeFifteenD, NULL );

  	pthread_exit(0); // Terminates the calling thread 

}

void *producer()
{
	int i, j; // Control variables, for loops. 

	for(j = 0; j < TIMESTORUN; j++)
	{
		pthread_mutex_lock(&mutex); // Lock the critical section, If the mutex is already locked, the calling thread blocks until the mutex becomes available
		if(chest.size == CAPACITY) // If the "chest" is already full, wait. 
		{
			printf("The chest contains booty, come and take it...\n");
			pthread_cond_wait(&full_cond, &mutex); // begin waiting on a full condition. 
		}
		else
		{
			//printf("The chest is updating....\n");
			chest.item[0] = pearls; // Place the current number of pearls in the "chest"
			chest.size++; // Indicate the chest is full. 
			for(i = 0; i < chest.size; i++)
			{
				printf("%d", chest.item[0]); // Print out the contents of the "chest" ... could probably do without this for loop.
			}
			printf("\n");
			pthread_cond_broadcast(&empty_cond); // Send a broadcast to all threads waiting on an "empty_cond", they can now continue
		}
		pthread_mutex_unlock(&mutex); // Unlock the critical section 
	}
}

void *consumeTenA()
{
	int i, j; // Control variables, for loops. 
	int pearlsTaken = 0; // Variable to store the amt of pearls taken per run

	for(j = 0; j < TIMESTORUN; j++)
	{
		pthread_mutex_lock(&mutex); // Lock the critical section, If the mutex is already locked, the calling thread blocks until the mutex becomes available
		if(pearls == 0) // If there's no more pearls left. 
		{
			resultsAndTerminate(); // Call funct to add up all the pearls taken by each thread, exit the program. 
		}
		if(chest.size == 0) // If the chest is already occupied by another thread. 
		{
			//printf("Yarr, this chest be empty....(A) \n");
			pthread_cond_wait(&empty_cond, &mutex); // Wait on an "empty_condition". 
		}
		else
		{
			printf("Yarr, Open, Seasme!(A)....\n");
			chest.size--; // Set the "chest" to empty 
			pearlsTaken = ceil( (pearls) * (.10) ); // Calculate the number of pearls to take, not a whole num? round up. 
			printf("Yarr, Pirate (A) Has Taken %d Pearls..\n", pearlsTaken);
			pirateATook += pearlsTaken; // Add the num of pearls taken to the total taken for this thread. 
			pearls-=pearlsTaken; // Subtract the num of pearls taken from the overall num of pearls. 
			printf("\n");
			pthread_cond_broadcast(&full_cond); // Every thread waiting on a "full_condition" can now continue. 
		}
		pthread_mutex_unlock(&mutex); // Unlock the critical section 
	}
	
}

void *consumeTenB()
{
	int i, j;
	int pearlsTaken = 0;

	for(j = 0; j < TIMESTORUN; j++)
	{
		pthread_mutex_lock(&mutex);
		if(pearls == 0)
		{
			resultsAndTerminate();
		}
		if(chest.size == 0)
		{
			//printf("Yarr, this chest be empty....(B) \n");
			pthread_cond_wait(&empty_cond, &mutex);
		}
		else
		{
			printf("Yarr, Open, Seasme!(B)....\n");
			chest.size--;
			pearlsTaken = ceil( (pearls) * (.10) ); 
			printf("Yarr, Pirate (B) Has Taken %d Pearls..\n", pearlsTaken);
			pirateBTook += pearlsTaken;
			pearls-=pearlsTaken;
			printf("\n");
			pthread_cond_broadcast(&full_cond);
		}
		pthread_mutex_unlock(&mutex);
	}
	
}

void *consumeFifteenC()
{
	int i, j;
	int pearlsTaken = 0;

	for(j = 0; j < TIMESTORUN; j++)
	{
		pthread_mutex_lock(&mutex);
		if(pearls == 0)
		{
			resultsAndTerminate();
		}
		if(chest.size == 0)
		{
			//printf("Yarr, this chest be empty....(C) \n");
			pthread_cond_wait(&empty_cond, &mutex);
		}
		else
		{
			printf("Yarr, Open, Watermelon!(C)....\n");
			chest.size--;
			pearlsTaken = ceil( (pearls) * (.15) ); 
			printf("Yarr, Pirate (C) Has Taken %d Pearls..\n", pearlsTaken);
			pirateCTook += pearlsTaken;
			pearls-=pearlsTaken;
			printf("\n");
			pthread_cond_broadcast(&full_cond);
		}
		pthread_mutex_unlock(&mutex);
	}
}

void *consumeFifteenD()
{
	int i, j;
	int pearlsTaken = 0;

	for(j = 0; j < TIMESTORUN; j++)
	{
		pthread_mutex_lock(&mutex);
		if(pearls == 0)
		{
			resultsAndTerminate();
		}
		if(chest.size == 0)
		{
			//printf("Yarr, this chest be empty....(D) \n");
			pthread_cond_wait(&empty_cond, &mutex);
		}
		else
		{
			printf("Yarr, Open, Watermelon!(D)....\n");
			chest.size--;
			pearlsTaken = ceil( (pearls) * (.15) ); 
			printf("Yarr, Pirate (D) Has Taken %d Pearls..\n", pearlsTaken);
			pirateDTook += pearlsTaken;
			pearls-=pearlsTaken;
			printf("\n");
			pthread_cond_broadcast(&full_cond);
		}
		pthread_mutex_unlock(&mutex);
	}
}

void resultsAndTerminate()
{
	int totalTaken = 0;
	totalTaken = pirateATook + pirateBTook + pirateCTook + pirateDTook;
	printf("There is no more treasure, the chest has been exhausted... \n");
	printf("Pirate (A) Took: %d pearls... \n", pirateATook);
	printf("Pirate (B) Took: %d pearls... \n", pirateBTook);
	printf("Pirate (C) Took: %d pearls... \n", pirateCTook);
	printf("Pirate (D) Took: %d pearls... \n", pirateDTook);
	printf("A total of %d pearls were taken from the chest...\n", totalTaken);
	exit(1);
}