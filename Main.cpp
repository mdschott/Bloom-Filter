/***************************************************************
Michael Schott
Main.cpp
Program 4
Runs loops that add elements to the BloomFilter, check for elements
outside the range of previously added elements being found, and
increasing the number of elements to be added. Outputs all of the 
calculated data.
***************************************************************/

#include "BloomFilter.hpp"
#include <iostream>
#include <math.h>


//Returns number of bits that should be used.
int GetBits(int n, float p)
{
	//Bits function provided
	return (-(n * log(p)) / pow(log(2), 2));
}


//Calculates how many hash functions to be used.
int GetHashes(int n, float p)
{
	int b = GetBits(n, p); //Number of bits to be used
	float i = (b / n);

	//Takes the ceiling to prevent a decimal value
	//The more hashes the better therefore ceiling
	//works better than floor
	return  ceil(i * log(2));
}



int main()
{
	//Begins at 8 for easy implementation within the while loop.
	//Number of Elements to be added
	float n = 8;
	//Dividend
	float q = 1;
	//Begins at 2 for easy implementation within the while loop.
	//Becomes the Divisor
	float p = 2;

	//Adds 16 up to n to the 23rd power elements.
	while (n < (pow(2, 23) + 1))
	{

		//Multiply number of elements by 2
		n *= 2;

		//Used to calculate the false positive rate
		//Increase dividend
		if (p < 1025)
			p = p * 2;

		//Creates the filter
		BloomFilter myFilter(n, GetHashes(n, (q / p)));

		//Add n elements
		for (int i = 0; i < n; i++)
		{
			myFilter.add((const uint8_t*)(&i), sizeof(int));
		}

		std::cout << "Bloom Filter Characteristics: " << std::endl;
		std::cout << "False Positive Rate: " << (q / p) << std::endl;
		std::cout << "Elements(N): " << n << std::endl;
		std::cout << "Bits(b): " << GetBits(n, (q / p)) << std::endl;
		std::cout << "Hash Functions (h): " << GetHashes(n, (q / p)) << std::endl;

		//count to calculate actual rate of false positives.
		float count = 0;

		//Checks if value not added to the table is in the table.
		for (int i = 1; i <= n; i++)
		{
			int x = i + n;
			if (myFilter.possiblyContains((const uint8_t*)(&x), sizeof(int)) == false)
				count++;
		}

		//Calculate the actual false positive rate.
		std::cout << "Rate of False Positives : " << (count / n) << std::endl;
		std::cout << std::endl;

	}

system("pause");

return 0;
};