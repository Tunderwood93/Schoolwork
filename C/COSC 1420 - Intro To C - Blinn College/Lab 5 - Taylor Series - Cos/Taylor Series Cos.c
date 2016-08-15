#include<stdio.h>
#include<math.h>
#include<ctype.h>

double p (double x, int n)
{  
    
  int i;
  double prod = 1.;
  for (i = 1, prod = 1.; i <= n; i++)
    prod = prod * x / i;
    
  return prod;
}
double mysin (double x)
{
  int i, j, sign; 
  double sum;
  
  for (i = 0, sign = 1, sum = 0.; i < 10; i++, sign = -sign)
    sum = sum + sign * p(x, 2 * i + 1);
    
  return sum;
} 

double mycos (double x)
{
  int i, sign; 
  double sum;
  
  for (i = 0, sign = 1, sum = 0.; i < 10; i++, sign = -sign)
    sum = sum + sign * p(x, 2 * i );
    
  return sum;
} 


double myExp (double x)
{
  int i, sign; 
  double sum;
  
 for (i = 0, sum = 0.; i < 10; i++)
    sum = sum + p(x, i);
    
  return sum;
} 

int main()
{
  double x;
  char more;
  do
  {
       printf("\n\t\t\t Input X: ");
       scanf ("%lf", &x);
       printf("\n\t\t\t\tLibrary Result  My Result");
       printf("\n\t\tsin(%6.2f)\t    %9.6f\t%9.6f", x, sin(x), mysin(x));
       printf("\n\t\tcos(%6.2f)\t    %9.6f\t%9.6f", x, cos(x), mycos(x));
       printf("\n\t\texp(%6.2f)\t    %9.6f\t%9.6f", x, exp(x), myExp(x));
       printf("\n\t\t\tDo more (Y/N) ?");
       scanf ("%s", &more);
       }while (more == 'y'||more == 'y');
}

