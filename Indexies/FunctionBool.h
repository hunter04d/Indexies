#pragma once
/*
 *Runtime heavy implementation
 * stores only the needed part
 * everything else is derived in member functions
 */
#include <vector>
#include "UtilityFunc.h"

struct FunctionBool
{
	std::vector<bool> vector;
	const size_t numberOfvars;
	FunctionBool(std::initializer_list<bool> init_list) : vector(init_list), numberOfvars(ceil(log2(init_list.size())))
	{
		size_t numberOfContituents(utility::fastpow2(numberOfvars));
		if (vector.size() != numberOfContituents)
		{
			vector.resize(numberOfContituents, false);
		}
	}

	FunctionBool(std::vector<bool> init_vector) : vector(init_vector), numberOfvars(ceil(log2(init_vector.size())))
	{
		size_t numberOfContituents(utility::fastpow2(numberOfvars));
		if(vector.size() != numberOfContituents)
		{
			vector.resize(numberOfContituents, false);
		}
	}

	//TODO: change string to vector<size_t> or better
	std::vector<size_t> PDNF()
	{
		std::vector<size_t> out;
		for (auto i = 0; i < vector.size(); ++i)
		{
			if(vector.at(i) == 1)
				out.push_back(i);
		}
		return out;
	}

	std::vector<size_t> PСNF()
	{
		std::vector<size_t> out;
		for (auto i = 0; i < vector.size(); ++i)
		{
			if (vector.at(i) == 0)
				out.push_back(i);
		}
		return out;
	}

};
