#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <stdio.h>

/*
	DEFINES
*/
#define CAPACITY 1
#define TIMESTORUN 45 // TIME TO RUN THE FOR LOOPS, MAY NEED TO BE TWEAKED. 80 semms to be a decent number. 
#define CHESTSIZE 5

/*
	FUNCTION PROTOTYPES
*/
void *producer();
void *consumeTenA();
void *consumeTenB();
void *consumeFifteenC();
void *consumeFifteenD();
void resultsAndTerminate();

/*
	STRUCT
*/
struct Data
{
	int item[CHESTSIZE];
	int size; 
};

/*
	GLOBAL VARIABLES
*/
int pearls = 1000;
pthread_mutex_t mutex;
pthread_cond_t full_cond;
pthread_cond_t empty_cond;
struct Data chest; 

int pirateATook = 0;
int pirateBTook = 0;
int pirateCTook = 0;
int pirateDTook = 0;



int main()
{
	int i;
	pthread_t threadID; 

	for(i = 0; i < CHESTSIZE; i++)
	{
		chest.item[i] = -1;
		chest.size = 0;
	}

	pthread_setconcurrency(5); // 1 producer thread + 4 consumer threads = 5 total threads running concurrently 

	pthread_create(&threadID, NULL, (void *(*)(void *))producer, NULL  );
  	pthread_create(&threadID, NULL, (void *(*)(void *))consumeTenA, NULL );
  	pthread_create(&threadID, NULL, (void *(*)(void *))consumeTenB, NULL );
  	pthread_create(&threadID, NULL, (void *(*)(void *))consumeFifteenC, NULL );
  	pthread_create(&threadID, NULL, (void *(*)(void *))consumeFifteenD, NULL );

  	pthread_exit(0);

}

void *producer()
{
	int i, j;
	sleep(1);
	for(j = 0; j < TIMESTORUN; j++)
	{
		//pthread_mutex_lock(&mutex);
		if(chest.size == CAPACITY)
		{
			printf("The chest contains booty, come and take it...\n");
			pthread_cond_wait(&full_cond, &mutex);
			//return;
		}
		else
		{
			//printf("The chest is updating....\n");
			chest.item[0] = pearls;
			chest.size++;
			for(i = 0; i < chest.size; i++)
			{
				printf("%d", chest.item[0]);
			}
			printf("\n");
			pthread_cond_broadcast(&empty_cond);
		}
		//pthread_mutex_unlock(&mutex);
	}
}

void *consumeTenA()
{
	int i, j;
	int pearlsTaken = 0;

	for(j = 0; j < TIMESTORUN; j++)
	{
		//pthread_mutex_lock(&mutex);
		if(pearls == 0)
		{
			resultsAndTerminate();
		}
		if(chest.size == 0)
		{
			//printf("Yarr, this chest be empty....(A) \n");
			pthread_cond_wait(&empty_cond, &mutex);
			//return;
		}
		else
		{
			printf("Yarr, Open, Seasme!(A)....\n");
			chest.size--;
			pearlsTaken = ceil( (pearls) * (.10) ); 
			printf("Yarr, Pirate (A) Has Taken %d Pearls..\n", pearlsTaken);
			pirateATook += pearlsTaken;
			pearls-=pearlsTaken;
			printf("\n");
			pthread_cond_broadcast(&full_cond);
		}
		//pthread_mutex_unlock(&mutex);
	}
	
}

void *consumeTenB()
{
	int i, j;
	int pearlsTaken = 0;

	for(j = 0; j < TIMESTORUN; j++)
	{
		//pthread_mutex_lock(&mutex);
		if(pearls == 0)
		{
			resultsAndTerminate();
		}
		if(chest.size == 0)
		{
			printf("Yarr, this chest be empty....(B) \n");
			pthread_cond_wait(&empty_cond, &mutex);
			//return;
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
		//pthread_mutex_unlock(&mutex);
	}
	
}

void *consumeFifteenC()
{
	int i, j;
	int pearlsTaken = 0;

	for(j = 0; j < TIMESTORUN; j++)
	{
		//pthread_mutex_lock(&mutex);
		if(pearls == 0)
		{
			resultsAndTerminate();
		}
		if(chest.size == 0)
		{
			printf("Yarr, this chest be empty....(C) \n");
			pthread_cond_wait(&empty_cond, &mutex);
			//return;
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
		//pthread_mutex_unlock(&mutex);
	}
}

void *consumeFifteenD()
{
	int i, j;
	int pearlsTaken = 0;

	for(j = 0; j < TIMESTORUN; j++)
	{
		//pthread_mutex_lock(&mutex);
		if(pearls == 0)
		{
			resultsAndTerminate();
		}
		if(chest.size == 0)
		{
			//printf("Yarr, this chest be empty....(D) \n");
			pthread_cond_wait(&empty_cond, &mutex);
			//return;
		
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
		//pthread_mutex_unlock(&mutex);
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
