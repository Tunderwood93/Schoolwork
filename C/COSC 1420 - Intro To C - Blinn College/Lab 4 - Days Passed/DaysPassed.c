//
//  lab 4.c
//  Lab 4
//
//  This program calculates the number of days passed in the year based on a user specified date.
//
//  Created by Trevor Underwood on 2/17/13.
//  Copyright (c) 2013 Trevor Underwood. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int main()
{
    int mm, dd, yy;
    char more;
    
    do
    {
        printf("\n\t\tPlease input the date (mm/dd/yy): ");
        scanf("%d/%d/%d", &mm,&dd,&yy);
        
        if(illegalDate(mm,dd,yy))
        {
            printf("\nSorry you've entered the date inccorectly, please try again. (mm/dd/yy)");
        }
        else
        {
            printf("\n\t\t There are %d days passed in %d", daysPassed(mm,dd,yy), yy); 
        }
        
        printf("\n\t\t\tDo more? (Y/N): ");
        scanf("%s" , &more);
        system("cls");
    }
    while(more == 'Y' || more == 'y');
}

int leapYear(int y)
{
    if (y % 4 == 0 && y % 100 != 0 || y % 400 == 0) 
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int illegalDate(int m, int d, int y)
{
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if(leapYear(y))
    {
        days[1] = 29;
    }
    if(m < 1 || m > 12)
    {
        return 1;
    }
    else if(d < 0 || d > days[m - 1]) //Changed from 12 to 1 
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int daysPassed(int m, int d, int y)
{
    int i, past = 0;
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    for(i = 0; i < m - 1; i++)
    {
        past = past + days[i];
    }
    
    past = past + d; 
    
    if(leapYear(y) && m > 2)
    {
        past++;
    }
    
    return past; 
}

