#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <thread>
#include <omp.h>

std::vector<unsigned int> hailstone(unsigned int n)
{
	std::vector<unsigned int> v;

	for (int i = n; i > 1; i = (i % 2 == 0 ? i / 2 : 3 * i + 1)) { v.push_back(i); }

	v.push_back(1);
	
	return v;
}

unsigned int hailstoneLength(unsigned int n)
{
	unsigned int tLength = 1;
	for (int i = n; i > 1; i = (i % 2 == 0 ? i / 2 : 3 * i + 1)) { tLength++; }
	return tLength;
}

std::pair<unsigned int, unsigned int> maxHailstoneLength(unsigned int start = 1, unsigned int end = 2, uint32_t step = 1)
{
	long long cVal = 0;
	uint32_t largest = 0;
	uint32_t largestNVal = start;

	#pragma omp master
	omp_set_num_threads(4);

	#pragma omp parallel for
	for (cVal = start; cVal <= end; cVal += step)
	{
		uint32_t cLength = hailstoneLength(cVal);
		if (cLength > largest)
		{
			largest = cLength;
			largestNVal = cVal; 
		}
	}

	return std::pair<uint32_t, uint32_t>(largest, largestNVal);
}

int main()
{
	
	auto largestSize = maxHailstoneLength(1, 50000000);
	std::cout << "Length: "<< largestSize.first << "\t NValue: " << largestSize.second << std::endl;
	
	std::cin.get();
	return 0;
}