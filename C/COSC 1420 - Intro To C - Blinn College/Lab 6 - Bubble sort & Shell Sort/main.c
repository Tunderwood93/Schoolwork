/*
 Written By: Trevor Underwood
 Date: Feb 27th 2013 
 version: 1.0 
 
 
 Demo Bubble Sort and Linear Search
 Your lab - 6 is writing code of shell sort and binary search 
 
*/

#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int x[])
{
    int i, j, temp;
    
    for(j = 0; j < 14; j++) // Double for loop 
    {
        for(i = 0; i < 14 - j; i++)
        {
            if(x[i] < x[i + 1]) // Swap Occurs here 
            {
                temp = x[i];
                x[i] = x[i + 1];
                x[i + 1] = temp; 
            }
        }
    }
}

int linearSearch(int x[], int temp)
{
    int i;
    
    for(i = 0; i < 15; i++)
    {
        if(x[i] == temp)
        {
            return i + 1; // Return Location
        }
    }
    return 0;
}

int main()
{
    int x[] = {39, 54, 32, 16, 28, 92, 46, 65, 78, 18, 82, 35, 68, 45, 29};
    int i, found, temp;
    char more;
    
    
    printf("\n\tUnsorted Sequence: ");
    
    for(i = 0; i < 15; i++)
    {
        printf("%d,", x[i]);
    }
    
    bubbleSort(x);
    
    printf("\n\tSorted Sqeuence: ");
    
    for(i = 0; i < 15; i++)
    {
        printf("%d,", x[i]);
    }
    
    do
    {
        printf("\n\t\tInput a number: ");
        scanf("%d", &temp);
        
        found = linearSearch(x, temp);
        
        if(found)
        {
            printf("\n\t\t%d is found at position %d", temp, found);
        }
        else
        {
            printf("\n\t\t%d is not found", temp);
        }
        
        printf("\n\t\t\tDo more? (Y/N): ");
        scanf("%s", &more);
        
    }
    while (more == 'y' || more == 'Y');
    
    return 0;
}
