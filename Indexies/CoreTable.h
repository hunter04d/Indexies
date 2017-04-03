#pragma once
#include <vector>
#include <utility>
#include <set>
#include "FunctionBool.h"
#include "VarTable.h"
#include <iostream>


class OneX_InCol_exception
{
	
};

class TermIndex
{
public:
	enum val
	{
		zero = 0,
		one = 1,
		crossed = 2
	};
private:
	size_t F_size;
	std::vector <val> F_term;
public:
	TermIndex(VarTable _init_val) : F_size(_init_val.Size()), F_term(F_size)
	{
		for(size_t i = 0 ; i <F_size ;++i)
		{
			F_term.at(i) = static_cast<val>( _init_val.at(i));
		}

	}
	bool operator==(const TermIndex&rhs) const
	{
		return F_term == rhs.F_term;
	}
	TermIndex CrossOutAtIndex(size_t index) const 
	{
		auto out = *this;
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
	auto& at(size_t i)
	{
		return F_term.at(i);
	}
};

struct Edge
{
	bool is_crossed = 0;
	TermIndex term;
	explicit Edge(TermIndex _term) : term(_term) { }
	explicit Edge(VarTable _init_val) : term(_init_val) { }
};

struct Cell
{
	bool includes_min_term = 0;
	bool deleted = 0;
};

class CoreTable
{
	size_t rows;
	size_t coloumlns;
	size_t num_of_vars;
	std::set<size_t> deletedCol;
	std::set<size_t> deletedRow;
	std::vector<Edge> min_terms;
	std::vector<Edge> terms;
	std::vector<std::vector<Cell>> F_table;

public:
	CoreTable(std::vector<TermIndex> _min_terms, FunctionBool _func) : rows(_min_terms.size()), coloumlns(_func.PDNF_Size()), num_of_vars(_func.numberOfvars), F_table(rows, std::vector<Cell>(coloumlns))
	{
		auto _PDNF = _func.PDNF();
		for (auto i = 0; i < coloumlns; ++i)
		{
			terms.emplace_back(VarTable(_func.numberOfvars, _PDNF.at(i)));
		}
		for (auto i = 0; i < rows; ++i)
		{
			min_terms.emplace_back(_min_terms.at(i));
		}
		SetIncludesTag();
	}

	void SetIncludesTag()
	{
		for (auto i = 0; i < rows; ++i)
		{
			for (auto j = 0; j< coloumlns; ++j)
			{
				if (terms.at(j).term.Includes(min_terms.at(i).term))
				{
					F_table.at(i).at(j).includes_min_term = true;
				}
			}
		}
	}
	// a  LOT OF TODO
private:
	int OneX_InCol(size_t _coloumn)
	{
		bool ret_tag = false;
		int out = -1;
		for (auto i = 0; i < rows; ++i)
		{
			if (F_table.at(i).at(_coloumn).includes_min_term==true && ret_tag == false)
			{
				ret_tag = true;
				out = i;
				continue;
			}
			if((F_table.at(i).at(_coloumn).includes_min_term == true) && ret_tag == true)
			{
				return -1;
			}
		}
		return out;
	}

public:
	void SetIsCrossed_MinTermTags_and_DeletedCellTags()
	{
		for (auto j = 0; j < coloumlns; ++j)
		{
			int r_row = OneX_InCol(j);
			if (r_row != -1)
			{
				if (deletedRow.count(j) == 0)
				{
					min_terms.at(r_row).is_crossed = true;
					deletedRow.insert(r_row);
					DeleteRow(r_row);
				}
			}
		}
	}

	void DeleteRow(int _row)
	{
		for (auto j = 0; j < coloumlns; ++j)
		{
			F_table.at(_row).at(j).deleted = true;
			if (F_table.at(_row).at(j).includes_min_term)
			{
				if (deletedCol.count(j) == 0)
				{
					deletedCol.insert(j);
					DeleteColoumn(j);
				}
			}
		}
	}

	void DeleteColoumn(size_t _coloumn)
	{
		terms.at(_coloumn).is_crossed = true;
		for (auto i = 0; i < rows; ++i)
		{
			F_table.at(i).at(_coloumn).deleted = true;
		}
	}

	void Print()
	{
		for (auto k = 0; k < num_of_vars; ++k)
		{
			std::cout << '-';
		}
		std::cout << '|';
		for (auto j = 0; j < coloumlns; ++j)
		{
	
				if (terms.at(j).is_crossed)
				{
					for (auto k1 = 0; k1 < num_of_vars; ++k1)
					{
						std::cout << '-';
					}
				}
				else
				{
					for (auto k1 = 0; k1 < num_of_vars; ++k1)
					{
						switch (terms.at(j).term.at(k1))
						{
							case 0:
							{
								std::cout << 0;
								break;
							}
							case 1:
							{
								std::cout << 1;
								break;
							}
							default: std::cout << '-';
						}
					}
				}
				std::cout << '|';
				
		}
		std::cout << '\n';
		for (auto i = 0; i < rows; ++i)
		{
			
				if (min_terms.at(i).is_crossed)
				{
					for (auto k1 = 0; k1 < num_of_vars; ++k1)
					{
						std::cout << '-';
					}
				}
				else
				{
					for (auto k1 = 0; k1 < num_of_vars; ++k1)
					{
						switch (min_terms.at(i).term.at(k1))
						{
							case 0:
							{
								std::cout << 0;
								break;
							}
							case 1:
							{
								std::cout << 1;
								break;
							}
							default: std::cout << '-';
						}
					}
			}
			std::cout << '|';
			for (auto j = 0; j < coloumlns; ++j)
			{
				if (F_table.at(i).at(j).deleted)
				{
					for (auto k1 = 0; k1 < num_of_vars; ++k1)
					{
						std::cout << '-';
					}
				}
				else if (F_table.at(i).at(j).includes_min_term)
				{
					std::cout << 'x';
					for (auto k1 = 1; k1 < num_of_vars; ++k1)
					{
						std::cout << ' ';
					}
				}
				else
				{
					for (auto k1 = 0; k1 < num_of_vars; ++k1)
					{
						std::cout << ' ';
					}
				}
				std::cout << '|';
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}
};
