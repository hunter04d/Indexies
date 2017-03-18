﻿#pragma once
#include <algorithm>
#include <string>
#include <vector>

namespace utility 
{
	std::vector<std::string> NcombK(unsigned N, unsigned K); // return vector of all possible combinations
	unsigned long long numberof_NcombK(unsigned N, unsigned K);
	std::vector<bool> toBinaryVector(size_t _Value, size_t _ofSize);
	bool hasString(const std::string& comparable, const std::string& comparison);

	inline size_t fastpow2(size_t pow)
	{
		if (pow == 0)
		{
			return 1;
		}
		return 2 << pow - 1;
	}
}
