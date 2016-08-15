    /*
	Compare library result and customized result.
*/

#include <stdio.h>
#include <math.h>

int main()
{
	double x, mysin();
	char more;

	do
	{
		printf("\n\t\t\tInput X: ");
		scanf("%lf", &x);
		printf("\n\t\t\tLibrary Result\tMy Result");
		printf("\n\t\tsin(%5.2f)\t%9.2f\t%9.6f", x, sin(x), mysin(x));

		//	Add cos() and exp() comparsions here

		printf("\n\t\t\tDo more(Y/N)?");
		scanf("%s", &more);
	}
	while(more == 'y' || more == 'Y');
}

double mysin(double x)
{
	double sum, quotient(); //(Original)power(), fact();
	int i, sign;

	for(i = 0, sum = 0, sign = 1; i < 20; i++, sign = -sign)
	{
		//sum = sum + sign * power(x, 2 * i + 1) / fact(2 * i + 1);
		sum = sum + sign * quotient(x, 2 * i + 1);
	}

	return sum;
}

// Remove the following two functions out of your lab 4.
/*(Original)
double power(double x, int n)
{
	int i;
	double prod;

	for(i = 0, prod = 1.; i < n; i++)
	{
		prod = prod * x;
	}

	return prod;
}

double fact(int n)
{
	int i;
	double prod;

	for(i = 1, prod = 1.; i <= n; i++)
	{
		prod = prod * i;
	}

	return prod;
}
*/
double quotient (double x, int n)
{
int i;
double prod;
double div;
double ans;

for(i = 0, prod = 1.; i <= n; i++)
{
prod = prod * x;
div = div * (i + 1);
ans = prod / div;
}

return prod;
}
