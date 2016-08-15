/**************************************************** 
Name: Trevor Underwood	
Date: Mar 15th, 2014
Problem Number: 4
Hours Spent: 7
CS2308 
Instructor: Komogortsev, TSU 

This header file provides function prototypes for the TsuPod project. 
This file must be included in other TsuPod source files. 
*****************************************************/

#ifndef tsuPod_h
#define tsuPod_h

#include <string>
#include <cmath>
#include <stdlib.h>
using namespace std;

const int NUM_SONGS = 8;
const int MEMORY_SIZE = 25;

struct TsuPod
{
	string title;
	string artist; 
	int size; 
};

void initalize();

int addSong(string songTitle, string artistName, int songSize);
int delSong(string songTitle);
int tsuPodWipe();

int memoryFree();
int memoryUsed();

int songCount();
void songList();

int shuffle();

int songCount();

#endif
