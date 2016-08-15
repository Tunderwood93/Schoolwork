/**************************************************** 
Name: Trevor Underwood	
Date: Mar 15th, 2014
Problem Number: 5
Hours Spent: 7
CS2308 
Instructor: Komogortsev, TSU 

This header file provides function prototypes for the TsuPod (5) project. 
This file must be included in other TsuPod source files. 
*****************************************************/

#ifndef tsuPod_h
#define tsuPod_h

#include <string>
#include <cmath>
#include <stdlib.h>
using namespace std;

//const int NUM_SONGS = 25;
//const int MEMORY_SIZE = 100;

/*struct TsuPod
{
	string title;
	string artist; 
	int size; 
};
*/

class TsuPodMemory
{
private:
	const int NUM_SONGS;
	const int MEMORY_SIZE;

public:
	void initalize();
	int tsuPodWipe();
	int findOpenMem();
	int memoryFree();
	int memoryUsed();
    int addSong(string songTitle, string artistName, int songSize);
	int delSong(string songTitle);
	int songCount();
	void songList();
	int shuffle();
    void song();
};

//extern TsuPod rockBox[NUM_SONGS];




//FUNCTIONS MOVED TO SONG.H
//int addSong(string songTitle, string artistName, int songSize);
//int delSong(string songTitle);
//int songCount();
//int songCount();
//void songList();
//int shuffle();

#endif
