#pragma once
#include <vector>
#include "UtilityFunc.h"


class VarTable
{
	size_t actualValue = 0;
	size_t NumOfVars = 3;
	std::vector<bool> F_VarTable;
public:
	explicit VarTable(size_t _NumOfVars = 3) : NumOfVars(_NumOfVars), F_VarTable(_NumOfVars, false)
	{
	}


	void Increment();

	void Decrement();

	void Set(size_t _value);

	void Resize(size_t _newSize)
	{
		NumOfVars = _newSize;
		F_VarTable.resize(_newSize, false);
	}

	size_t decimal() const
	{
		return actualValue;
	}

	std::vector<bool>::const_reference at(size_t pos) const
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
