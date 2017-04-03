#pragma once
#include "VarTable.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <tuple>
#include "CoreTable.h"
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

	void RemoveFromFunction(FunctionBool& _func);

	std::set<size_t> GetUnremovedColPos();


	TermIndex ConvertS_Index_to_TermIndex(size_t _i, size_t _j)
	{
		TermIndex out(VarTable(log2(size), _i));
		const auto& str = naming.at(_j);
		char name_ptr = 'a';
		std::vector<size_t> pos;
		for (auto i = 0; i < str.size(); ++i)
		{
		pos.push_back(str.at(i) - name_ptr);
		}
		for (auto i = 0; i < log2(size); ++i)
		{
			if (std::find(pos.begin(), pos.end(), i) == pos.end())
			{
				out.at(i) = TermIndex::crossed;
			}
		}
		return out;
	}


	std::vector<TermIndex> GetTermsInCoreForm()
	{
		std::vector<TermIndex> out;
		auto needed_cols = GetUnremovedColPos();
		auto it = needed_cols.begin();
			while (it != needed_cols.end())
			{
				for (auto i = 0; i < size; ++i)
				{
				if (F_Table.at(i).at(*it).is_removed == false)
				{
					auto insert_val = ConvertS_Index_to_TermIndex(i, *it);
					if (std::find(out.begin(), out.end(), insert_val) == out.end())
					{
						out.push_back(insert_val);
					}
				}
				
			}
				++it;
		}
		return out;
	}



};

inline void IndexTable::RemoveFromFunction(FunctionBool& _func)
{
	for (size_t i = 0; i < size; ++i)
	{
		if (_func.vector.at(i) == 0)
		{
			RemoveRow(i);
		}
		
	}
	RemoveSimilar();
	Consume();
}


