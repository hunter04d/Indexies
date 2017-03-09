#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace utility 
{
	std::vector<std::string> NcombK(unsigned N, unsigned K); // return vector of all possible combinations
	unsigned long long numberof_NcombK(unsigned N, unsigned K);
	std::vector<bool> toBinaryVector(size_t _Value, size_t _ofSize);
	bool hasString(std::string comparable, std::string comparison);


}
