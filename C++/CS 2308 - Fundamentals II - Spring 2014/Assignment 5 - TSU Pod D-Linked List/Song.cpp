/****************************************************
Name: Trevor Underwood
Date: April 5th, 2014
Problem Number: 5
Hours Spent: 
CS2308
Instructor: Komogortsev, TSU
*****************************************************/

#include "tsuPod.h"
#include "Song.h"

#include <iostream>
#include <string>
#include <cmath>
using namespace std;


songData Song;

string songData::getTitle()
{
    return title;
}

void songData::setTitle(string inTitle)
{
    title = inTitle;
}

string songData::getArtist()
{
    return artist;
}

void songData::setArtist(string inArtist)
{
    artist = inArtist;
}

int songData::getSize()
{
    return size;
}

void songData::setSize(int songSize)
{
    size = songSize;
}

