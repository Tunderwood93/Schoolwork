/****************************************************
Name: Trevor Underwood
Date: Feb 21st, 2014
Problem Number:	3	
CS2308
Instructor: Komogortsev, TSU
*****************************************************/

//This file provides the implementation of the life.h header file.
//THERE ARE 76 CHARS IN A LINE, 61 LINES TOTAL, 4,636 CHARS TOTAL. 



#include "life.h"
#include <iostream>
#include <new>
#include <windows.h>
#include <cmath>
#include <ctime>

using namespace std;

//GLOBAL VARIABLES
int ROWS = 0;         //stores the number of rows in the grid
int COLUMNS = 0;      //stores the number of rows in the grid
int charsRead = 0;
char c;
char ** mainArray;
int ** neighborArray; 
char ** tempArray;
ifstream initialState;

void openFile(const char * file, ifstream &initialState)
{
	initialState.open(file, ios::in);

	if (!initialState)
	{
		cout << "The file failed to open, please verify the txt file is in root directory of exe" << endl;
		cout << "Terminating Program" << endl;
		initialState.close();
		exit(EXIT_FAILURE);
	}
}

//This function reads input file for subsequent prosessing 
void populateWorld (const char * file)
{
	openFile(file, initialState);

	while (initialState.get() != '\n')			//Lines 52 - 55 are responsible for reading the width / columns in the file
	{
		charsRead++;
	}
	COLUMNS = charsRead;
	charsRead = 0;
	initialState.seekg(ios::beg); 

	while (!initialState.eof())				  //Lines 60 - 75 are responsible for determining the number of lines / rows in a file.
	{

		if (initialState.get() == '\n')
		{
			//Do Nothing if newline is Detected. 
		}
		else if (initialState.peek() == EOF)
		{
			charsRead++;
		}
		else
		{
			charsRead++;
		}
	}
	ROWS = (charsRead / COLUMNS);
	charsRead = 0;
	initialState.seekg(ios::beg);
/*
	cout << "There are " << COLUMNS << " columns" << endl;			These lines are for debugging purposes
	cout << "There are " << ROWS << " rows" << endl << endl;	Show the number of rows & cols in dynamic array.
*/
	SetWindow(COLUMNS * 1.075, ROWS * 1.075);  // X,Y

	mainArray = new char * [ROWS];						 //Lines 85 - 90 Allocate memory to the "mainArray"
														//    mainArray is a dynamic 2D char array
	for (int i = 0; i < ROWS; i++)
	{
		mainArray[i] = new	char[COLUMNS];
	}                                                  

	for (int i = 0; i < ROWS; i++)					//Lines 92 - 110 read the data from the input file.
	{												//Once the data is read it's assigned to the mainArray.
		for (int j = 0; j < COLUMNS; j++)			//If the loop encounters a '1' it is represented as an "*"
		{											//If the loop encounters a '0' it is represented as a ' ' 
			c = initialState.get();
			if (c == '\n')
			{
				c = initialState.get();
			}
			if(c == '1')
			{
				mainArray[i][j] = '*';
			}
			else if (c == '0')
			{
				mainArray[i][j] = ' ';
			}
		}
	}

	initialState.close();
}

//This function outputs the grid for current generation
//There is an adjustable delay (in ms) between generations "Sleep(x)"
void showWorld ()
{
	for (int i = 0; i < ROWS; i++)
	{
		cout << '\n';
		for (int j = 0; j < COLUMNS; j++)
		{
			cout << mainArray[i][j];
		}
	}
	Sleep(500);
}

//This function creats new geneneration grid from the old generation grid
void iterateGeneration ()
{
	neighborArray = new int * [ROWS];							//Lines 132 - 137 allocate memory for the "neighborArray"
																//neighborArray is a 2D dynamic int array
	for (int i = 0; i < ROWS; i++)
	{
		neighborArray[i] = new int[COLUMNS];
	}

	for (int i = 0; i < ROWS; i++)								//Lines 139 - 145 initializes neighborArray with 0's 
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			neighborArray[i][j] = 0;
		}
	}


	for (int i = 0; i < ROWS; i++)			//LOGIC LOOP. 
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			for (int k = -1; k < 2; k++)
			{
				for (int l = -1; l < 2; l++)
				{
					if (!(k == 0 && l == 0)) // Stops from reading self-cell
					{
						if (!(i + k < 0 || i + k >= ROWS) && !(j + l < 0 || j + l >= COLUMNS)) //Stops reading out of bounds
						{		
							if (mainArray[i + k][j + l] == '*')
							{
								//cout << "mainArray[" << (i) << "][" << (j) << "] = " << mainArray[i][j] << endl;
								neighborArray[i][j] += 1;
							}
						}
					}
				}
			}
		}
	}

	tempArray = new char *[ROWS];								//This loop creates the dynamic tempArray.

	for (int i = 0; i < ROWS; i++)
	{
		tempArray[i] = new char[COLUMNS];
	}

	for (int i = 0; i < ROWS; i++)								//Lines 179 - 185 initialize tempArray with 0's 
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			tempArray[i][j] = ' ';
		}
	}

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			switch (neighborArray[i][j])
			{
			case 0:
			case 1:
				//dies
				break;
			case 2:
			case 3:
				if (mainArray[i][j] == ' ' && neighborArray[i][j] == 3)
				{
					// New cell is born
					tempArray[i][j] = '*';
				}
				else if (mainArray[i][j] != ' ')
				{
					// Cell remains unchanged.
					tempArray[i][j] = '*';
				}
				break;
			default:
				break;
				// Cell dies
			}
		}
	}
	cout << endl;
	
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			mainArray[i][j] = tempArray[i][j];
		}
	}
}

void SetWindow(int Width, int Height)		//This function resizes the console window. 
{
	_COORD coord;
	coord.X = Width;
	coord.Y = Height;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
	SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
}