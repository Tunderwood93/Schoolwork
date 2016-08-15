/*
  Name: Trevor Underwood
  Class: COSC 1420 - 301

  This is Lab - 9.

  This is a program that calculates your bowling score.
*/

#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int j, i;
    int score = 0, ball, a, b2, k, x;
    int b[2][12];
    int s[10], s2[10];
    char more = 'Y';

    x = 12;
    do {
    printf ("\n\t\tWelcome to Blinn Bowling Center");
    a = 1;
    for (i = 1; i < 11; i++)
    {
        j = 1;

        if (i < 10)
        {
           printf ("\n           Frame - %d", i);
           do
           {
             printf ("\n\t Ball - %d : ", j);
             scanf ("%d", &ball);

            if (score + ball > 10)
            {
               printf ("\n\t\t\t        Illegal score, do one more time...");
               j = j - 1;
            }
            else
                if (ball == 10 && j == 1)
                {
                   printf ("\t\t\t        Congradulations! It is STRIKE...");
                   b[j-1][i-1] = ball;
                   b[j][i-1] = 0;
                   j = j + 2;
                }
                else
                    if (score + ball == 10)
                    {
                       printf ("\t\t\t        Not bad, it is SPARE...");
                       b[j-1][i-1] = ball;
                       j = j + 1;
                    }
                    else
                        if (ball < 10 && j == 1)
                        {
                           b[j-1][i-1] = ball;
                           score = ball;
                        }
                        else
                        {
                            printf ("\n\t\t\t        Need work harder, dude!");
                            b[j-1][i-1] = ball;
                        }
            j = j + 1;
           }
           while (j < 3);
        }
        else
        {
            b2 = 1;
            printf ("\n\t   Frame - 10");
            while (a == 1)
            {
                  switch (b2)
                  {
                         case 1:
                              printf ("\n\t Ball - 1 : ");
                              scanf ("%d", &ball);
                              if (ball == 10)
                              {
                                 printf ("\n\t\t\t        Congradulations! It is STRIKE...");
                                 b[0][9] = ball;
                                 b[1][9] = 0;
                                 x = 12;
                                 b2 = 2;
                              }
                              else
                                  if (ball > 10)
                                  {
                                     printf ("\n\t\t   Illegal score, do one more time...");
                                     b2 = 1;
                                  }
                                  else
                                  {
                                      b[0][9] = ball;
                                      score = ball;
                                      b2 = 3;
                                  }
                              break;

                         case 2:
                              printf ("\n\t Extra - 1 : ");
                              scanf ("%d", &ball);
                              if (ball == 10)
                              {
                                 b[0][10] = ball;
                                 b2 = 4;
                              }
                              else
                                  if (ball > 10)
                                  {
                                     printf ("\n\t\t   Illegal score, do one more time...");
                                     b2 = 2;
                                  }
                                  else
                                  {
                                    b[0][10] = ball;
                                    score = ball;
                                    b2 = 5;
                                  }
                              break;

                         case 3:
                             printf("\n\t Ball -2 : ");
                             scanf ("%d", &ball);
                             if (score + ball == 10)
                             {
                                 printf ("\n\t\t    Not bad, it is SPARE...");
                                 b[1][9] = ball;
                                 score = 0;
                                 x = 11;
                                 b2 = 6;
                             }
                              else
                                  if (ball + score > 10)
                                  {
                                     printf ("\n\t\t   Illegal score, do one more time...");
                                     b2 = 3;
                                  }
                                  else
                                  {
                                     b[1][9] = ball;
                                     a = 0;
                                     x = 10;
                                  }
                              break;

                         case 4:
                             printf ("\n\t Extra - 2 : ");
                             scanf ("%d", &ball);
                             if (ball == 10)
                              {
                                 b[0][11] = ball;
                                 a = 0;
                              }
                              else
                                  if (ball > 10)
                                  {
                                     printf ("\n\t\t   Illegal score, do one more time...");
                                     b2 = 4;
                                  }
                                  else
                                  {
                                      b[0][11] = ball;
                                      a = 0;
                                  }
                              break;

                         case 5:
                            printf ("\n\t Extra - 2 : ");
                            scanf ("%d", &ball);
                            if (ball + score <= 10)
                            {
                                b[0][11] = ball;
                                a = 0;
                            }
                            else
                                printf("\n\t\t   Illegal score, do one more time...");

                            break;

                         case 6:
                            printf ("\n\t Extra - 1 : ");
                            scanf ("%d", &ball);
                            if (ball <= 10)
                            {
                                b[0][10] = ball;
                                a = 0;
                            }
                            else
                                printf("\n\t\t   Illegal score, do one more time...");
                            break;
                  }

            }
        }


        score = 0;
    }

    for (i = 0; i <10; i++)
    {
        if(b[0][i] == 10)
        {
            if (b[0][i+1] == 10)
                s[i] = 20 + b[0][i+2];
            else
            s[i] = 10 + b[0][i+1]+ b[1][i+1];
        }
        else
        {
            if( b[0][i] + b[1][i] == 10)
                s[i] = 10 + b[0][i];
            else
                s[i] = b[0][i] + b[1][i];
        }
    }

    printf ("\n\n\t   Frame  -   1   2   3   4   5   6   7   8   9  10  Xtr-1 Xtr-2");
    printf ("\n");
    printf ("\t Ball - 1 : ");
    for (i = 0; i < 1; i++)
    {
        for (j = 0; j < x; j++)
            printf ("%3d ", b[i][j]);
        printf (" \n ");
    }
    s2[0] = s[0];
    for (k = 1; k < 10; k++)
        s2[k] = s[k] + s2[k-1];
        printf ("\t Ball - 2 : ");
    for (i = 1; i < 2; i++)
    {
        for (j = 0; j < 10; j++)
            printf (" %2d ", b[i][j]);
        printf (" \n ");
    }
    printf ("\t   Score : ");
    for (i = 0; i < 10; i++)
    {
        printf (" %3d", s2[i]);

    }

     printf ("\n\n\t\t Do you want to do more (Y/N)? ");
     scanf ("%s", &more);
    }while (more == 'Y' || more == 'y');

    return 0;

}

