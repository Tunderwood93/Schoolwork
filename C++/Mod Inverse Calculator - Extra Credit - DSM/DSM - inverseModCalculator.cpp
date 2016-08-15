/*
	Name: Trevor Underwood
	Date: 11/09/14
	Problem Number: Extra Credit Assignment
	Instructor: Ferrero, TSU
 */

#include <iostream> 
#include <stdio.h>

using namespace std; 

/*
function:    pause
parameter:   none
returns:     nothing, simply pauses the terminal window after execution. 
			 portable implentation. 
 */ 
void pause()
{
  cout << "Press [ ENTER ] to continue..." << endl;
  cin.clear();
  cin.get();
  cin.ignore();
}

/*
function:    isCoPrime
parameter:   Two ints, a & m 
returns:     true / false boolean if the ints passed to the function are co-prime or not. 
 */
bool isCoPrime(int a, int m)
{
	int gcd = 0; 
	int temp = 0; 

	//Swap values if A > M & M >= 0
	//Program dumps garbage without the swap for small values
	// ex a = 30 & m = 5.  
	if(a > m && m >= 0)
	{
		temp = m;
		m = a; 
		a = temp;

		temp = 0;
	} 
		

	for(int i = 2; i < m; i++)
	{
		if(a % i == 0 && m % i == 0)
		{
			gcd = i;
		}
    }

    if (gcd == 0)
    {
    	return true; 
    }
    else
    {
    	return false; 
    }
}

/*
function:    mod_Inv
parameter:   Two ints, a & m 
returns:     The modular inverse of the two ints passed to the function
 */
int mod_Inv (int a, int b)
{
	int b0 = b, t, q;
	int x0 = 0;
    int x1 = 1; 

	if(b == 1)
	{
		return 1; 
	}

	while(a > 1)
	{
		q = a / b; 
		t = b; 
		b = a % b;
		a = t; 
		t = x0; 
		x0 = x1 - q * x0;
		x1 = t; 
	}

	if(x1 < 0)
	{
		x1 += b0;
		return x1; 
	}
	else if(x1 > 0) 
	{
		return x1;
	}
    else; 

}

int main()
{
	char more = 'y'; 
	int a, m, x, temp; //integers to store a, m, and a temp value for swapping

	while(more == 'y' || more == 'Y') // crappy way to loop the program after each calculation.
	{
		cout << "Welcome to the A mod M inverse calculator" << endl 
             << "Please enter the values for A, and the value for M" << endl
             << "Note that this program only works for positive integers" << endl << endl;
		
        cout << "A = "; 
		cin >> a;
		cout << "M = ";
		cin >> m;
		
		cout << endl;

		// If the two ints passed are co-prime, calculate the mod_Inv. 
		if(isCoPrime(a,m) == true)
		{
			cout << "The inverse of " << a << " mod " << m << " is " << mod_Inv(a,m) << endl << endl;
			
	
    		pause();
		}
		else
		{
			cout << "Integers " << a << " and " << m << " are not co-prime." << endl
    		     << "You cannot find the inverse of A mod M if the two integers are not Co-prime" << endl
    		     << "Remember, two ints are coprime if their GCD = 1" << endl << endl;
    		     
            pause(); 
		}
	}
}
