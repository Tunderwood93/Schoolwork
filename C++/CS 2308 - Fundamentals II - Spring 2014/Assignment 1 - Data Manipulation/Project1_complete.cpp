/*
Name: **********
Date: 1/28/14
Problem Number: 1
Instructor: Komogortsev, TSU
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

void formatDate( ofstream& fout, char date_array[] );
double convertTemp ( double temperature );
double charToFloat( char temp_array[], double& temperature, const int TEMP_ARRAY_SIZE );

int main ()
{
	const int TEMP_ARRAY_SIZE = 7,
			  DATE_ARRAY_SIZE = 13;

	int file_input_lines = 0,
		loop_count = 0;

	double temperature = 0.0,
			temp_avg = 0.0;

	char date_array[DATE_ARRAY_SIZE],
	     temp_array[TEMP_ARRAY_SIZE];

	ifstream fin;
	ofstream fout;

	fin.open("biodata.dat");

	if ( !fin )                                //Terminates program if input file fails to open.
	{
		cout << "Program terminated. Input file failed to open.";
		fin.close();
		return 1;
	}

	fout.open("filtered_biodata.dat");

	if ( !fout )                               //Terminates program if output file fails to open.
	{
		cout << "Program terminated. Output file failed to open.";
		fin.close();
		fout.close();
		return 2;
	}

	fout << "BIODATA Formatted Output" << endl << endl;

	fin >> file_input_lines;

	for ( ; loop_count < file_input_lines; ++loop_count )
	{
		fin >> date_array >> temp_array;

		if ( temp_array[1] == '-' )                       //Terminates the program if it runs
		{                                                 //into a negative temperature.
			fout << "Negative temperature readings not allowed." << endl
				 << "Program Terminated.";
			return 3;
		}

		if ( ( temp_array[0] != 'C' ) && ( temp_array[0] != 'F' ) )
		{
			fout << "Temperature measurement '" << temp_array[0]            //Terminates the program if it runs
			     << "' unit not recognized. Must be 'F' or 'C'." << endl    //into an invalid temperature unit
				 << "Program Terminated. ";
			return 4;
		}

		temperature = charToFloat( temp_array, temperature, TEMP_ARRAY_SIZE );
		if ( temp_array[0] == 'F' )
			temperature = convertTemp ( temperature );
		fout << fixed << setprecision(2) << temperature;
		formatDate( fout, date_array );
		temp_avg = temp_avg + temperature;
	}

	temp_avg = temp_avg / loop_count;
	fout << endl << "Average Temp --- " << temp_avg << " C";

	fin.close();
	fout.close();

	return 0;
}

/*
function:    charToFloat
parameter:   temp_array ( char ) temperature ( double ) and constant TEMP_ARRAY_SIZE ( int )
returns:     The float value of a temperature stored as a character array.
 */
double charToFloat( char temp_array[], double& temperature, const int TEMP_ARRAY_SIZE )
{
	int count = 1,
		decimal_place = 0;

	temperature = 0.0;

	for ( int h = 1; h < TEMP_ARRAY_SIZE; ++h ) // This loop fills the non-decimal elements of the char
	{                                           // array with the integer value of the element, and
        if ( temp_array[h] == '.' )             // calculates the decimal_place.
		{
			decimal_place = h - 1;              // -1 because it doesn't count the first element of
		}	                                    // the array when calculating the decimal_place.

		else
			temp_array[h] = temp_array[h] - 48; //converts ascii value to integer value
   	}

    for ( int j = 1; j < TEMP_ARRAY_SIZE - 1; ++j )                 //This loop turns the elements in the char
    {                                                               //array with the correct integer value into
                                                                    //a float.
    	if( j <= decimal_place )                                    //This if statement multiplies elements to the
    	    temperature = temperature + ( temp_array[j] *           //left of the decimal_place by degrees of 10.
    			    	  ( pow ( 10.0, decimal_place - j ) ) );

    	else if( temp_array[j] == '.')                              //Do nothing with the element holding the
    		continue;                                               //place.

    	else
    	{
    		temperature = temperature + temp_array[j] * 1.0 /      //This statement multiplies elements to the
    				      ( pow ( 10.0, decimal_place - count ) ); //right of the decimal_place by the reciprocal
    		--count;                                               //of degrees of 10.
    	}
    }
	return temperature;
}

/*
function:    formatDate
parameter:   fout ( ofstream ) and date_array[] ( char )
returns:     Outputs a timestamp stored in a character into a human readable format.
 */
void formatDate( ofstream& fout, char date_array[] )
{
	fout << " C --- recorded on "<< date_array[4] << date_array[5] << "/"
		 << date_array[6] << date_array[7] << "/" << date_array[0] << date_array[1]
		 << date_array[2] << date_array[3] << " at " << date_array[8]
		 << date_array[9] << date_array[10] << date_array[11] << endl;
}

/*
function:    convertTime
parameter:   temperature ( double )
returns:     Converts a Fahrenheit temperature measurement into Celcius.
 */
double convertTemp ( double temperature )
{
	temperature = ( temperature - 32 ) * (5.0/9);
	return temperature;
}