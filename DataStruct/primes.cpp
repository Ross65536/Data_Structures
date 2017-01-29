
#include "stdafx.h"
#include <iostream>
#include <limits>

using namespace std;



bool isPrime(int number) {

	if (number < 2) return false;
	if (number == 2) return true;
	if (number % 2 == 0) return false;
	for (int i = 3; (i*i) <= number; i += 2) {
		if (number % i == 0) return false;
	}
	return true;

}



void print_hash_table_primes()
{
	size_t lower_limit = 64;
	cout << sizeof(size_t) << endl << sizeof(long long) << endl;
	cout << "{ ";

	for (size_t i = lower_limit + 1 ; i - 3 < numeric_limits<size_t>::max() ; i+= 2)
	{
		if (i == 3)
			break;

		if (isPrime(i))
		{
			if (lower_limit < i)
			{
				cout << i << ", ";
				lower_limit *= 2;
				i = lower_limit + 1;
			}
		}
	}


}