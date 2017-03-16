#pragma once
/*
 *Runtime heavy implementation
 * stores only the needed part
 * everything else is derived in member functions
 */
#include <vector>
#include "UtilityFunc.h"
#include "IndexTable.h"
class FunctionBool
{
	std::vector<bool> vector;
	const size_t numberOfvars;
public:
	friend void IndexTable::RemoveFromFunction(FunctionBool &_func, bool _tag);
	FunctionBool(std::vector<bool> init_vector) : vector(init_vector), numberOfvars(ceil(log2(init_vector.size())))
	{
		size_t numberOfContituents(utility::fastpow2(numberOfvars));
		if(vector.size() != numberOfContituents)
		{
			vector.resize(numberOfContituents, false);
		}
	}

	//TODO: change string to vector<size_t> or better
	std::string DDNF()
	{
		std::string out;
		for (auto i = 0; i < vector.size(); ++i)
		{
			if(vector.at(i) == 1)
			{
				out.push_back(i + '0');
			}
		}
		return out;
	}

	std::string DKNF()
	{
		std::string out;
		for (auto i = 0; i < vector.size(); ++i)
		{
			if (vector.at(i) == 0)
			{
				out.push_back(i + '0');
			}
		}
		return out;
	}

};
