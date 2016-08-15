/**************************************************** 
Name: Trevor Underwood	
Date: Jan 27th 2014 
Problem Number: 1
Instructor: Komogortsev, TSU 
*****************************************************/ 
#include <fstream>
#include <iostream>
#include <iomanip>
 
using namespace std;

void tStampConvert(char *input, char *year, char *month, char *day, char *times) // not
{
	for(int i = 0; i < 12; i++) //not this 
	{
		if(i < 4)
		{
			year[i] = input[i];
		}
		else if(i > 3 && i < 6)
		{
			month[i-4] = input[i];
		}
		else if(i > 5 && i < 8)
		{
			day[i-6] = input[i];
		}
		else
		{
			times[i-8] = input[i];
		}

	}
	cout << "recorded on " << month << '/' << day << '/' << year << " at " << times << ".\n";
	cout << input;
	




}

int main ()
{
	char numOfLines[800];
	char year[4];
	char *month[2];
	char *day[2];
	char *times[4];
	int SIZE = 0, iNumofLines = 0;
	char input[1500];



	cout << "This program takes an unformated Biodata.dat file and formats it \n";
	cout << "the output will be saved to a new file or appended to an existing file. \n\n";
	cout << "**Please place the Biodata file to format in the root directory of the .exe** \n\n";

	//Opening the file for input
	fstream bioDataIn("biodata.dat", ios::in);
	fstream bioDataOut("filtered_biodata.dat", ios::out | ios::app);

	if(!bioDataIn)
	{
		cout << "File not found, make sure the biodata.dat file is in the root directory \n";
		cout << "Press any key to exit. \n";
		system("pause>nul");
	}

	//Read items from the file using \n as a delimiter.

	bioDataIn.getline(numOfLines, '\n');
	iNumofLines = atoi(numOfLines); 		//Type casting the char from numOfLines into an int.
	//cout << iNumofLines << endl;			//This line will display the number of lines to read - Use for Debugging

	while(!bioDataIn.eof())
	{
		bioDataIn.getline(input, 25);
		tStampConvert(input, year, *month, *day, *times);
		//cout << input << endl;
		bioDataOut << input << endl;
	}


	//close the files
	bioDataIn.close();
	bioDataOut.close();


	//Pause the command line
	system("pause>nul");
	return 0;
}


