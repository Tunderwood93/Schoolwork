
#ifdef _linux 
#define LINUX true
#define WINDOWS false
#endif

#ifdef _WIN32
#define LINUX false 
#define WINDOWS true
#endif


#include <iostream>
#include <fstream>

#include "life.h"

const char FILE_NAME[] = "glider_gun_fight.txt";

using namespace std;

const int NUM_GENERATIONS = 10; //set to a smaller number for debugging

int main() 
{
    populateWorld(FILE_NAME);
        
	showWorld();
	
    for (int iteration = 0; iteration < NUM_GENERATIONS; iteration++) 
    {
	
        if (WINDOWS)
           system("cls"); //Windows only
        else
           system("clear"); //Linux only
    
        iterateGeneration();
    
        showWorld();
    }

	if (WINDOWS)
        system("PAUSE");
    
    return 0;
}
