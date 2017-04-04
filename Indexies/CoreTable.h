#pragma once
#include <vector>
#include <utility>
#include <set>
#include "FunctionBool.h"
#include "VarTable.h"
#include <iostream>
#include "TermIndex.h"


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
		for (auto i = 0; i < rows; ++i)
		{
			for (auto j = 0; j < coloumlns; ++j)
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
public:
	void GetCore()
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
