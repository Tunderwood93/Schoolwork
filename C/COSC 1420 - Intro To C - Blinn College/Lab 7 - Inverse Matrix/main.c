# include <stdio.h>
# include <math.h>
# include <stdlib.h>

double subIt(double x[][3], double y[][3], double z[][3])
{
  int i, j;
  
  for (i = 0; i<3; i++)
    for (j = 0; j < 3; j++)
       x[i][j] = y[i][j] - z[i][j];
       return 0;     
}

void prodIt(double e[][3], double a[][3], double c[][3],  double d[][3])
{
   int i, j, k, f = 0;
   
           
   do{
  
   for (i = 0; i<3; i++)
       for (j = 0; j < 3; j++)
           e[i][j] = e[i][j] + a[i][j];
   for (i = 0; i < 3; i++)
       for (j = 0; j < 3; j++){
        d[i][j] = 0;
            for (k = 0; k < 3; k++)
                d[i][j] = d[i][j] + a[i][k] * c[k][j];
                }
   for (i = 0; i<3; i++)
        for (j = 0; j < 3; j++)
            a[i][j] = d[i][j]; 
                  
   f = f + 1;
}  while (f < 20);   
}

void checkIt( double x[3][3], double y[3][3], double z[3][3])
{
       int i, j, k;
       for (i = 0; i < 3; i++)
           for (j = 0; j < 3; j++)
               {z[i][j] = 0;
               for (k = 0; k < 3; k++)
                    z[i][j] = z[i][j] + x[i][k] * y[k][j];  }    
}

void printIt ( double a[] [3], double b[][3])
{
     int i, j;
     
     for( i = 0; i<3; i++)
          {printf("\n\t\t\t");
          for(j = 0; j<3 ; j++)
                printf("%6.2f", a[i][j]);
          printf("\t");
          for (j = 0; j<3; j++)
              printf("%6.2f", b[i][j]);
              printf("\t");
          
              }
}

int main ()
{
    int i, j;
    double id[3][3] = {1., 0., 0., 0., 1., 0., 0., 0., 1.};
    double inva[3][3], b[3][3], pb[3][3], tempb[3][3], check[3][3];
    double a[3][3] = { .5, 1., 0., 0., .67, 0., -.5, -1., .67};
    
    subIt(b,  id,  a);
    
    for (i = 0; i<3; i++)
       for (j = 0; j < 3; j++)
           pb[i][j] = b[i][j];
    for (i = 0; i<3; i++)
        for (j = 0; j < 3; j++)
            inva[i][j] = id[i][j];
    
    prodIt(inva, pb,  b,  tempb);
     
    checkIt(a, inva, check);
    
    printf("\n\t\t\t  MATRIX INVA \t\t  MATRIX CHECK");
    printIt(inva, check);
                
    system("pause");    
    
}
