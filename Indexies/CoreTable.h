#pragma once
#include <vector>
#include <utility>
#include "FunctionBool.h"
#include "VarTable.h"

struct Cell
{
	bool includes_min_term = 0;
	bool	 deleted = 0;
};

class TermIndex
{
public:
	enum val
	{
		zero =0,
		one = 1,
		crossed = 2
	};
private:
	size_t F_size;
	std::vector <val> F_term;
public:
	TermIndex(size_t _size, VarTable _init_val) : F_size(_size), F_term(_size)
	{
		for(size_t i = 0 ; i <F_size ;++i)
		{
			F_term.at(i) = static_cast<val>( _init_val.at(i));
		}

	}
	TermIndex CrossOutAtIndex(size_t index) const 
	{
		TermIndex out = *this;
		out.F_term.at(index) = crossed;
		return out;
	}
	bool Includes(TermIndex& _smaller_term)
	{
		for(size_t i = 0; i < F_size; ++i)
		{
			if((F_term.at(i) == _smaller_term.F_term.at(i)) || _smaller_term.F_term.at(i) == crossed )
			{
				continue;
			}
			 return false;
		}
		return true;
	}
};

struct Edge
{
	bool is_crossed = 0;
	TermIndex term;
	Edge(TermIndex _term) : term(_term) { }
};

class CoreTable
{
	std::vector<Edge> min_terms;
	std::vector<Edge> terms;
	std::vector<std::vector<Cell>> F_table;
 public:
	CoreTable(std::vector<TermIndex> _min_terms, FunctionBool _func): min_terms(_min_terms.size())
	{
		
	}
};
