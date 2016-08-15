#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main()
{
	float f1, f2, c1, c2;
	int choice = 0; 
	char more = 'y';

	while(more == 'y' || more == 'Y')
	{
		printf ("\n\t\tRelationship between Fahrenheit and Celsius");
		printf ("\n\n\n\t\t\t1) Fahrenheit - > Celsius");
		printf ("\n\n\t\t\t2) Celsius - > Fahrenheit");
		printf ("\n\n\n\t\t\t      Choice (1/2)?: ");
		scanf  ("%u", &choice);

		if(choice == 1)
		{
            system("cls");
			printf ("\nPlease enter Fahrenheit value to be converted to Celsius: ");
			scanf ("%g", &f1);
            f2 = (f1 - 32) * 5/9;
			printf("\n%6.2f", f2);
		}
		else if(choice == 2)
		{
            system("cls");
			printf ("\nPlease enter Celsius value to be converted to Fahrenheit: ");
			scanf ("%g", &c1);
            c2 = (c1 * 9/5) + 32;
			printf("\n%6.2f", c2);

		}
		else
		{
			printf("\nYour choice is invalid, please try again.");
		}

		printf ("\nDo more? (Y/N): ");
		scanf  ("%s", &more);
	}

	return 0;
}
