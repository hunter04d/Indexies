#pragma once
#include <vector>
#include "UtilityFunc.h"


class VarTable
{
	size_t actualValue = 0;
	size_t NumOfVars = 3;
	std::vector<bool> F_VarTable;
public:
	VarTable(size_t _NumOfVars = 3) : NumOfVars(_NumOfVars), F_VarTable(_NumOfVars, false)
	{
	}

#define ofSize ,

	void Increment()
	{
		if (actualValue < (2 << NumOfVars - 1) - 1) ++actualValue;
		else {	Set(0);}
		for (int  i = NumOfVars - 1; i >=0; --i)
		{
			if(!F_VarTable.at(i))
			{
				F_VarTable.at(i) = true;
				for(int j = i+1; j <NumOfVars; ++j)
				{
					F_VarTable.at(j) = 0;
				}
				break;
			}
		}
	}

	void Decrement()
	{
		if (actualValue < (2 << NumOfVars - 1) - 1 && actualValue > 0) --actualValue;
		else actualValue = (2 << NumOfVars - 1) - 1;
		F_VarTable = utility::toBinaryVector(actualValue ofSize NumOfVars);
		
	}

	void Set(size_t _value)
	{
		if (_value < (2 << NumOfVars - 1))
		{
			actualValue = _value;
		}
		else actualValue = (2 << NumOfVars - 1) - 1;
		F_VarTable = utility::toBinaryVector(actualValue ofSize NumOfVars);
	}

	void Resize(size_t _newSize)
	{
		NumOfVars = _newSize;
		F_VarTable.resize(_newSize, false);
	}
#undef ofSize
	size_t decimal() const
	{
		return actualValue;
	}

	std::vector<bool>::const_reference  at(size_t pos) const
	{
		return F_VarTable.at(pos);
	}

	std::vector<bool>::const_reference front() const
	{
		return F_VarTable.front();
	}

	std::vector<bool>::const_reference back() const
	{
		return F_VarTable.back();
	}

	friend std::ostream& operator<<(std::ostream& _cout, VarTable& _VarTable);
};

inline std::ostream& operator<<(std::ostream& _cout, VarTable& _VarTable)
{
	for (size_t i = 0; i < _VarTable.NumOfVars; ++i)
	{
		_cout << _VarTable.F_VarTable[i];
	}
	return _cout;
}
