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
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
using namespace std;



//TsuPod rockBox[NUM_SONGS]; // Accesses the struct defined in header and allocates 25 spaces of memory. 

/*
	This function initializes the TsuPod Structure
	Once the function has completed running the statement
	"Struct initialized" is printed
*/
void TsuPodMemory::initalize()
{
	for(int i = 0; i < NUM_SONGS; i++)
	{
		rockBox[i].title = "";
		rockBox[i].artist = "";
		rockBox[i].size = 0;
	}
	cout << "struct initialized" << endl << endl;
}

/*
	This function looks for an open location in the array index
	to store a song. Once an open location in the index is found
	that index location is returned.

	A slot is defined as free if the size is 0

	This function returns the following:
		* returns open position in the index "i" if an open space is found
		* returns -1 if no open spaces are found in the index
*/
int findOpenMem()
{
	for(int i = 0; i < NUM_SONGS; i++)
	{
		if(rockBox[i].size <= 0) 
		{
			return i;  
		}
	}
	return -1;
}

/*
	This function clears all song data

	This function returns the following:
		*  returns 1 and outputs "TsuPod has been wiped clean" on success
	
	This function cannot fail.
*/
int tsuPodWipe()
{
	for(int i = 0; i < NUM_SONGS; i++)
	{
		rockBox[i].title = "";
		rockBox[i].artist = "";
		rockBox[i].size = 0;
	}
	cout << "TsuPod has been wiped clean" << endl;
	return 1;
}

/*
	This function checks the amount of memory the
	songs have taken up

	This function solely sums the size of all of 
	the songs.
	
	This function returns the following:
		*  The value of the memory used
*/
int memoryUsed()
{
	int memory = 0;

	for(int i = 0; i < NUM_SONGS; i++)
	{
		memory += rockBox[i].size;
	}

	return memory;
}

/*
	This function checks the amount of memory remaining

	This function takes our maximum amount of memory
	and subtracts the total amount we have used. It then
	checks if that number is less than 0 and, if so, 
	sets our remaining memory to 0.

	This function returns the following:
		*  The value of the memory remaining
*/
int memoryFree()
{
	int memory = MEMORY_SIZE - memoryUsed();

	if(memory < 0)
	{
		memory = 0;
	}

	return memory; 
}

/*
 This function is responsible for adding a song into memory
 
 This function accepts the following:
 * Song title
 * Artist Name
 * Size of the song (MB)
 
 This function returns the following:
 *  returns 1 if a song is successfully added
 *  returns -1 if there isn't enough memory to add the specified song
 *  returns -2 if there are no available spaces in the index to add a song.
 *  returns -3 if the song fails to add for some other reason.
 */
int addSong(string songTitle, string artistName, int songSize)
{
	int index = findOpenMem();
	int freeMem = memoryFree();
    
	if ((freeMem >= songSize) && (songTitle != "") && (artistName != "") && (songSize > 0) && (index >= 0))
	{
		rockBox[index].title = songTitle;
		rockBox[index].artist = artistName;
		rockBox[index].size = songSize;
		return 1;
	}
	else if (freeMem < songSize)
	{
		cout << "Not enough memory to add song" << endl;
		return -1;
	}
	else if (index == -1)
	{
		cout << "No avaliable slots to add another song, try deleting one first." << endl;
		return -2;
	}
	else
	{
		cout << "Song addition failure" << endl;
		return -3;
	}
}

/*
 This function is responsible for deleting a song from memory
 
 This function accepts the following:
 * Song title
 
 This function iterates through the songs until it finds one with
 a title matching the parameter of the function, then resets
 the memory to its initial state. Then it outputs "Song Removed"
 on success.
 
 This function returns the following:
 *  returns 0 if a song is successfully removed
 *  returns -1 if the song is not found
 */
int delSong(string songTitle)
{
	for (int i = 0; i < NUM_SONGS; i++)
	{
		if (rockBox[i].title == songTitle)
		{
			rockBox[i].title = "";
			rockBox[i].artist = "";
			rockBox[i].size = 0;
            
			cout << "Song Removed" << endl;
            
			return 0;
		}
	}
	cout << "You can't remove a song that doesn't exist" << endl;
	return -1;
    
}

/*
 This function is outputs the list of our songs in the order
 they were stored. It checks the size to determine if a
 song exists at that location of memory, and if not, outputs
 the location and "Empty Space." Otherwise, it outputs the
 location followed by title, artist, and size.
 
 The function then displays the remaining free space and
 remaining slots avilable for songs.
 */
void songList()
{
	cout << "******** Song List: (#, Song Title, Song Artist, Song Size(MB)) ********" << endl << endl;
    
	for (int i = 0; i < NUM_SONGS; i++)
	{
		if (rockBox[i].size == 0)
		{
			cout << (i + 1) << "\t" << "Empty Space" << endl;
		}
		else
		{
			cout << (i + 1) << "\t" << rockBox[i].title << "\t" << rockBox[i].artist << "\t" << rockBox[i].size << endl;
		}
	}
    
	cout << endl;
    
	int freeMem = memoryFree();
	int avaliableSongs = (NUM_SONGS - songCount());
    
	cout << "Memory Avaliable (MB): " << freeMem << " There are: " << avaliableSongs << " slots free" << endl;
	cout << "************************************************************************" << endl;
	cout << endl;
}

/*
 This function shuffles the songs
 
 This function checks to see if there are at least
 two songs. This function then iterates through the songs,
 assigning a new random number between 0 and one
 less than the number of songs (for 8 slots).
 
 This function returns the following:
 *  returns 1 and outputs "Shuffled" on success
 *  returns -1 and fails if there are less than two songs
 */
int shuffle()
{
	int numSongs = songCount();
    
	if (numSongs < 2)
	{
		cout << "You can't shuffle less than two songs" << endl;
		return -1;
	}
    
	for (int i = 0; i < (NUM_SONGS - 1); i++)
	{
		int r = i + (rand() % (NUM_SONGS - i));
		TsuPod temp = rockBox[i];
		rockBox[i] = rockBox[r];
		rockBox[r] = temp;
	}
    
	cout << "Shuffled" << endl;
	return 1;
}

/*
 This function checks our amount of songs
 
 This function searches through the slots and
 determines if there are values for songs. If
 so, they are added to a count.
 
 This function returns the following:
 *  The number of valid songs
 */
int songCount()
{
	int count = 0;
    
	for (int i = 0; i < NUM_SONGS; i++)
	{
		if (rockBox[i].size <= 0) continue;
		count++;
	}
	return count;
}


