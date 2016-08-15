/****************************************************
Name:
Date:
Problem Number:
CS2308
Instructor: Komogortsev, TSU
*****************************************************/

//This header file provides the prototypes of the function definitions
//for the project.

#ifndef life_h
#define life_h

#include <iostream>
#include <fstream>
#include <new>
#include <Windows.h>


using namespace std;

void SetWindow(int Width, int Height);
void openFile(const char * file);
void populateWorld(const char * file);
void showWorld();
void iterateGeneration();


#endif
