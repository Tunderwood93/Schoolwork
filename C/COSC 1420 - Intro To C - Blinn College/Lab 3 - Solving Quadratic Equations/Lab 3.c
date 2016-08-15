#include <stdio.h>
#include <math.h>
/*
         Lab 3 - Solving Quadratic Equations 
         Written by: Trevor Underwood
         Date: Sept 17th 2012
         Version: 1.0 Final
         
This program will solve quadratic equations including those with complex roots. 
The way this works is when the 3 values for A,B,C are entered by the user, 
a discriminate is calculated (b*b - 4*a*c). 

If the discriminate is positive you have two real solutions. 
If the discriminate is negitive you get imaginary solutions.
if the discriminate is zero you get just one solution.  
*/

int main()
{
    float a, b, c, root1, root2, real, dis, complex; 
    char more = 'y';
    
    while(more == 'y' || more == 'Y')
    {
    printf("\n\t\tSolve quadritic equation for giving A, B, C coefficient");
    printf("\n\tPlease input A: ");
    scanf("%g", &a);
    printf("\n\tPlease input B: ");
    scanf("%g", &b);
    printf("\n\tPlease input C: ");
    scanf("%g", &c);
      
     dis = ((b*b) - (4*a*c));
     root1 = (-b + sqrt(b*b - 4*a*c)) / (2*a);
     root2 = (-b - sqrt(b*b - 4*a*c)) / (2*a);
     real = -b / (2*a);
     complex = sqrt(dis * -1)/(2*a); 

     if (dis < 0)
     {
        printf("\nTwo complex roots, ");
        printf("X1 =%6.3g + ", real);
        printf("%6.3gi", complex);     
        
        printf(", X2 =%6.3g,", real);
        printf(" -%6.3gi", complex);
     }
     else if (a == 0 && b != 0 && c != 0)
     {
          printf("\n Single Root, X = %g", -c/b);
     }
     else if (a == 0 && b == 0 && c == 0)
     {
          printf("\nInfinite Solutions");
     }
     else if (a == 0 && b == 0 && c != 0)
     {
        printf("\nContradict Equation");
     }
     else if (dis > 0)
     {
        printf("\nThe first root value = %g ", root1);
        printf("\nThe second root value = %g", root2);       
     }
     else if (dis == 0)
     {
         printf("\nRepeated root, X = %g", real);    
     }
      
    printf("\nDo more? (Y/N):");
    scanf("%s", &more);
     
    }
 
}

