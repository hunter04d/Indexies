#include "stdafx.h"
#include "UtilityFunc.h"


std::vector<std::string> utility::NcombK(unsigned N, unsigned K) // return vector of all possible combinations
{
	std::string bitmask(K, 1); // K leading 1's
	bitmask.resize(N, 0); // N-K trailing 0's					 
						  // print integers and permute bitmask
	std::vector<std::string> temp(utility::numberof_NcombK(N, K));
	size_t counter = 0;
	do
	{
		for (size_t i = 0; i < N; ++i) // [0..N-1] integers
		{
			if (bitmask[i])
			{
				temp.at(counter).push_back(i + '0');
			}
		}
		++counter;
	} while (prev_permutation(bitmask.begin(), bitmask.end()));
	return temp;
}

unsigned long long utility::numberof_NcombK(unsigned N, unsigned K)
{
	if (K > N) return 0;
	if (K * 2 > N) K = N - K;
	if (K == 0) return 1;
	int result = N;
	for (int i = 2; i <= K; ++i)
	{
		result *= (N - i + 1);
		result /= i;
	}
	return result;
}
std::vector<bool>  utility::toBinaryVector(size_t _Value, size_t _ofSize)
{
	//Some overhead reduction to reduce over calculations 
	if (_Value == 0)
	{
		return std::vector<bool>(_ofSize, false);
	}
	if (_Value == (2 << _ofSize - 1) - 1)
	{
		return std::vector<bool>(_ofSize, true);
	}
	size_t i = 1;
	std::vector<bool> temp(_ofSize, false);
	while (_Value != 0)
	{
		*(temp.end() - i) = _Value % 2 ? true : false;
		_Value /= 2;
		++i;
	}
	return temp;
}
bool utility::hasString(std::string comparable, std::string comparison)// comparable should be less than comparison
{
	size_t numberofmatches = comparable.size(), counter = 0;
	for(size_t i = 0; i < numberofmatches; ++i)
	{
		if (comparison.find(comparable.at(i))!= std::string::npos)
		{
			++counter;
		}
		/*for (size_t j = 0; j < comparison.size(); ++j)
		{
			if(comparable.at(i) == comparison.at(j))
			{
				++counter;
			}
		}*/
	}
	if (counter == numberofmatches)
		{return true;}
		return false;
	
}

size_t utility::fastpow2(size_t pow)
{
	if(pow == 0)
	{
		return 1;
	}
	size_t result = 2;
	for(auto i = 1; i < pow; ++i)
	{
		result *= 2;
	}
	return result;
}

