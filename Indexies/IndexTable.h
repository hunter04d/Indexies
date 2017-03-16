#pragma once
#include "VarTable.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <tuple>
//#include "FunctionBool.h"
class FunctionBool; // forward declaration

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
public:
	explicit IndexTable(size_t NumOfVars);
/*
	void RemoveRows(std::string constituents) //deprecated and bad practice, need to change 
	{
		for (int i = 0; i < constituents.size(); ++i)
		{
			RemoveRow(constituents.at(i) - '0');
		}
	}
*/


	/*
	* Main functions for removing unneeded combinations
	*/
	void RemoveRow(size_t row) // using number set, should use function direct interaction with constituents
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

	void RemoveRowFromFunction(FunctionBool& _func, bool _tag);
	
};

#include "FunctionBool.h"

inline void IndexTable::RemoveRowFromFunction(FunctionBool & _func, bool _tag)
{

}


