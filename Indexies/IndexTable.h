#pragma once
#include "VarTable.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <tuple>
#include "FunctionBool.h"
#include <set>

struct S_Index
{
	bool is_removed = false;
	std::vector<bool> value;

};

//TODO: this class is a mess, proper implementation is in order
class IndexTable
{
	const size_t size;
	std::vector<std::vector<S_Index>> F_Table;
	std::vector<std::string> naming;
	bool tag = true;
public:
	explicit IndexTable(size_t NumOfVars);



	/*
	* Main functions for removing unneeded combinations
	*/
	void RemoveRow(size_t row) // used in access with FunctionBool object
	{
		for (int i = 0; i < size; ++i)
		{
			F_Table.at(row).at(i).is_removed = true;
		}
	}

	void RemoveSimilar();

	void Consume();

	void PrintFile();

	void PrintNames();

	void Print();

	void RemoveFromFunction(FunctionBool& _func, bool _tag);

	std::set<size_t> GetUnremovedColPos();

};

inline void IndexTable::RemoveFromFunction(FunctionBool& _func, bool _tag)
{
	tag = _tag;
	for (size_t i = 0; i < size; ++i)
	{
		if (_func.vector.at(i) != _tag)
		{
			RemoveRow(i);
		}
		RemoveSimilar();
		Consume();
	}
}


