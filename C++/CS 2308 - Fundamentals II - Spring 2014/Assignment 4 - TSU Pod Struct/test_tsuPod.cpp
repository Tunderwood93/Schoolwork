/**************************************************** 
Name: Trevor Underwood
Date: March 15th, 2014
Problem Number: 4
Hours Spent: 7
CS2308 
Instructor: Komogortsev, TSU 
*****************************************************/

#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "tsuPod.h"
using namespace std;

int main() 
{
    int retCode; // Returns from functions
     
    // Following code initializes the tsuPod 
    initalize();
  
    // Following code lists all songs located in tsuPod memeory 
    songList();
    cout << endl;
    
    // Following code tests tsuPod input functionality 
    retCode = addSong("Runaway1", "Bon Jovi1", 1);
    retCode = addSong("Runaway2", "Bon Jovi2", 2);
    retCode = addSong("Runaway3", "Bon Jovi3", 3);
    retCode = addSong("Runaway4", "Bon Jovi4", 1);
    retCode = addSong("Runaway5", "Bon Jovi5", 5);
    retCode = addSong("Runaway6", "Bon Jovi6", 6);
    retCode = addSong("Runaway7", "Bon Jovi7", 1);
    retCode = addSong("Runaway8", "Bon Jovi8", 1);
    cout << retCode << endl;   
    songList();
    cout << endl;

    //The following code test successful song removal
    retCode = delSong("Runaway8");
    cout << retCode << endl;
    songList();
    cout << endl;
    
    //The following code tests unsuccessful song addition due to lack of memory
    retCode = addSong("BigSong", "Big Artist", 36);
    cout << retCode << endl;
    songList();
    cout << endl;

    //Following code tests unsuccessful tsuPod song removal functionality         
    retCode = delSong("Runaway100");
    cout << retCode << endl;    
    songList();
    cout << endl;
  
    //Following code tests tsuPod song shuffling functionality      
    shuffle();
    cout << endl;
    songList();
    cout << endl;
    
    //The following code wipes the TsuPod clean.
    retCode = tsuPodWipe();
    cout << retCode << endl;
    songList();
    cout << endl;
    
    //system("PAUSE"); Windows command
    
}
