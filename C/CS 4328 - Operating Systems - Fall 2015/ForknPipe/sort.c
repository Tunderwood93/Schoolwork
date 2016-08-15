/*

2. The second program "sort.c" reads in a list of names from stdin and 
order them in alphabetical order. For the same letter in upper- and
lower-cases, you put the lower-case first. Assume there are 
no more than 10 names and the sequence is read until an EOF is encountered. 

For the above example, the output should be:

CAL
LU
NT

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char usrEntry[10][5];
	char tempArray[10][5];
	int i =0, j, k, x;

	//printf("Welcome to the sort.c program \n");
	//printf("This program will read up to 10 user entered stock names, or until the user inputs CTRL + D \n");
	//printf("The program will then output the user input stock names in alphabetical order \n");
	//printf("if you enter two identical names in different case IE: FMF and fmf, lower-case will be output first \n");


	while(i != 10 && scanf("%s", usrEntry[i]) == 1)
	{
		//printf("The name you just entered was %s \n", &usrEntry[i]);
		i++;
	} 


	for(j = 1; j < i + 1; j++)
		for(k = 1; k < i + 1; k++)
		{
			if(strcmp(usrEntry[k-1], usrEntry[k]) > 0) //if(strcmp(usrEntry[k-1], usrEntry[k]) > 0)
			{
				//strncpy(tempArray[k], usrEntry[k - 1], sizeof(tempArray));
				//strncpy(usrEntry[k - 1], usrEntry[k], sizeof(usrEntry));
				//strncpy(usrEntry[k], tempArray[k], sizeof(usrEntry)); 
				strcpy(tempArray, usrEntry[k-1]);
				strcpy(usrEntry[k - 1], usrEntry[k]);
				strcpy(usrEntry[k], tempArray);
			}
		}
	
	for(x = 0; x < i; x++)
		printf("here are the strings in order %s \n", usrEntry[x]); 

	
	return 0; 

}