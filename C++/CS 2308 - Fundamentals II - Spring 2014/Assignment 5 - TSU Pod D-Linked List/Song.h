/****************************************************
Name: Trevor Underwood
Date: Apr 5th, 2014
Problem Number: 5
Hours Spent: 
CS2308
Instructor: Komogortsev, TSU

This header file provides song function prototypes for the TsuPod (5) project.
This file must be included in other TsuPod source files.
*****************************************************/
#ifndef Song_h
#define Song_h

#include <string>
class songData
{
private:
	string title;
	string artist;
	int size;
    
    int * upPointer;
    int * downPointer;
    
public:
    
    string getTitle();
    void setTitle(string inTitle);
    
    string getArtist();
    void setArtist(string inArtist);
    
    int getSize();
    void setSize(int songSize);
    
    int getUpPointer();
    void setUpPointer();
    
    int getDownPointer();
    void setDownPointer();
    
};
#endif