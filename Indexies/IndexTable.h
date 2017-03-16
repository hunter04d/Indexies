﻿#pragma once
#include "VarTable.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
//#include "FunctionBool.h"
class FunctionBool; // foward declaration

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
	explicit IndexTable(size_t NumOfVars) :size(2 << NumOfVars - 1), F_Table(size, std::vector<S_Index>(size))
	{
		VarTable temp(NumOfVars);
		naming.resize(size);
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < NumOfVars; ++j)
			{
				if (i == 0)
					naming.at(j).push_back(j + 'a');
				F_Table.at(i).at(j).value.resize(1);
				F_Table.at(i).at(j).value.at(0) = temp.at(j);
			}
			temp.Increment();
		}
		temp.Set(0);
		size_t counter(NumOfVars);
		std::vector<std::string> combinationsRef;
		for (auto K = 2; K <= NumOfVars; ++K)
		{
			combinationsRef = utility::NcombK(NumOfVars, K);
			size_t CurrNumOfComb = utility::numberof_NcombK(NumOfVars, K);
			for (auto j = counter; j < counter + CurrNumOfComb; ++j)
			{
				for (auto i = 0; i < size; ++i)
				{
					F_Table.at(i).at(j).value.resize(K);
					for (auto k = 0; k < K; ++k)
					{
						F_Table.at(i).at(j).value.at(k) = temp.at(combinationsRef.at(j - counter).at(k) - '0');
						if (i == 0)
							naming.at(j).push_back(combinationsRef.at(j - counter).at(k) - '0' + 'a');
					}
					temp.Increment();
				}
				temp.Set(0);
			}
			counter += CurrNumOfComb;
		}
	}

	void PrintNames()
	{
		std::cout << ' ';
		for (int i = 0; i < size; ++i)
		{
			std::cout << naming.at(i) << "  ";
		}
	}
	void Print()
	{
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				std::cout << std::setw(2);

				for (int k = 0; k < F_Table.at(i).at(j).value.size(); ++k)
				{
					if (F_Table.at(i).at(j).is_removed)
					{
						if (k == 0)
						{
							std::cout << 'R';
						}
						else std::cout << ' ';
					}
					else std::cout << F_Table.at(i).at(j).value.at(k);
				}
				std::cout << " ";
			}
			std::cout << std::endl;
		}
	}
	void RemoveRows(std::string constituents)
	{
		for (int i = 0; i < constituents.size(); ++i)
		{
			RemoveRow(constituents.at(i) - '0');
		}
	}

	void RemoveRow(size_t row) // using number set, should use function direct interaction with constituents
	{
		for (int i = 0; i < size; ++i)
		{
			F_Table.at(row).at(i).is_removed = true;
		}
	}
	void RemoveRemovedInColoumn(size_t coloumn)
	{
		for (int i = 0; i < size; ++i)
		{
			if(F_Table.at(i).at(coloumn).is_removed)
			{
				RemoveSimilar(coloumn, i);
			}
		}
	}
	void RemoveRemoved()
	{
		for (int i = 0; i < size; ++i)
		{
			RemoveRemovedInColoumn(i);
		}
	}
private:
	void RemoveSimilar(size_t coloumn, size_t _i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (F_Table.at(j).at(coloumn).is_removed || j == _i) continue;
			if (F_Table.at(_i).at(coloumn).value == F_Table.at(j).at(coloumn).value)
			{
				F_Table.at(j).at(coloumn).is_removed = true;
			}
		}
	}
public:
	void PrintFile()
	{
		std::ofstream fout;
		fout.open("Text.txt");
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				fout << std::setw(2);
				for (int k = 0; k < F_Table.at(i).at(j).value.size(); ++k)
				{

					fout << F_Table.at(i).at(j).value.at(k);
				}
				fout << " ";
			}
			fout << std::endl;
		}	
		fout.close();
	}
private:
	void ConsumeInRow(size_t row)
	{
		size_t N = static_cast<size_t>(log2(size));
		for(size_t K = 1 ; K < N - 1 ;++K)
		{
			size_t startforI = [&K, &N]()
			{
				size_t sum = 0;
				for (int i = 1; i <= K; ++i)
				{
					sum += utility::numberof_NcombK(N, i);
				}
				return sum;
			}();
			for(size_t i = startforI; i < startforI + utility::numberof_NcombK(N, K + 1); ++i)
			{
				if(F_Table.at(row).at(i).is_removed == false)
				{
					for(size_t j = startforI + utility::numberof_NcombK(N, K+1); j < size; ++j )
					{
						if(F_Table.at(row).at(j).is_removed == false)
						{
							if(utility::hasString(naming.at(i), naming.at(j)))
							{
								F_Table.at(row).at(j).is_removed = true;
							}
						}
					}
				}
			}
		}
	}

public:
	void Consume()
	{
		for (int i = 0; i < size; ++i)
		{
			ConsumeInRow(i);
		}
	}

	 void RemoveFromFunction(FunctionBool& _func, bool _tag);
};

#include "FunctionBool.h"


