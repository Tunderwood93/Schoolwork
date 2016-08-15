/*

1. The first program "find.c" should read in stock symbol names and value per share from stdin. 
find.c should print out those stocks whose value per share is below $10.
The program terminates when an EOF is encountered. 

    For example, the following are the inputs to "find.c": 
MOT $16.14
NT  $3.65
LU  $3.05
CAL $9.57
Ctrl-D (to terminate the input.)
         
    then "find.c" produces the output: 
NT
LU
CAL

*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	struct usrStock
	{
		char stockSymb[50];
		float stockPrice; 
	};

	int i = 0, j;
	struct usrStock stock[10];

	//printf("Welcome to the stock finder program. \n");
	//printf("This progam will take up to 10 user entered stocks and prices and print out the stocks who's share prices are below $10. \n");
	//printf("Please enter your stock(s) in the following format MOT 16.14 \n");
	//printf("When finished entering your stock(s) press CRTL + D. \n");
	// While not EOF (Ctrl -Z in Windows) or (ctrl - d in unix)	
	while(scanf("%s %f", stock[i].stockSymb, &stock[i].stockPrice) == 2 && i != 9)
	{ 
		//Send the user input values into the array. 
		//printf("The stock you just entered was %s with a price of %.2f \n", &stock[i].stockSymb, stock[i].stockPrice);
		i++;
	}

	for(j = 1; j < i; j++)
	{
		if(stock[j].stockPrice < 10)
		{
			printf("%s \n ", stock[j].stockSymb);
		}
	}
	return 0; 
}

