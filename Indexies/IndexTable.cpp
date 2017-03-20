#include "stdafx.h"
#include "IndexTable.h"
#include "FunctionBool.h"

IndexTable::IndexTable(size_t NumOfVars) :size(2 << NumOfVars - 1), F_Table(size, std::vector<S_Index>(size))
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

void IndexTable::PrintNames()
{
	std::cout << ' ';
	for (int i = 0; i < size; ++i)
	{
		std::cout << naming.at(i) << "  ";
	}
}

void IndexTable::Print()
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

std::vector<size_t> IndexTable::GetUnremovedPos()
{
	std::vector<size_t> out;
	for (int row = 0; row < size; ++row)
	{
		for (int coloumn = 0; coloumn < size; ++coloumn)
		{
			if (F_Table.at(row).at(coloumn).is_removed == false)
			{
				out.push_back(coloumn);
			}
		}
	}
	out.erase(std::unique(out.begin(), out.end()), out.end());
	return out;
}

void IndexTable::RemoveSimilar()
{
	for (int coloumn = 0; coloumn < size; ++coloumn)
	{
		for (int row = 0; row < size; ++row)
		{
			if (F_Table.at(row).at(coloumn).is_removed == true)
			{
				for (int k = 0; k < size; ++k)
				{
					if (F_Table.at(k).at(coloumn).is_removed || k == row) continue;
					if (F_Table.at(row).at(coloumn).value == F_Table.at(k).at(coloumn).value)
					{
						F_Table.at(k).at(coloumn).is_removed = true;
					}
				}
			}
		}
	}
}

void IndexTable::PrintFile()
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

void IndexTable::Consume()
{
	size_t N = static_cast<size_t>(log2(size));
	for (size_t row = 0; row < size; ++row)
	{
		for (size_t K = 0; K < N - 1;++K)
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
			for (size_t i = startforI; i < startforI + utility::numberof_NcombK(N, K + 1); ++i)
			{
				if (F_Table.at(row).at(i).is_removed == false)
				{
					for (size_t j = startforI + utility::numberof_NcombK(N, K + 1); j < size; ++j)
					{
						if (F_Table.at(row).at(j).is_removed == false)
						{
							if (utility::hasString(naming.at(i), naming.at(j)))
							{
								F_Table.at(row).at(j).is_removed = true;
							}
						}
					}
				}
			}
		}
	}
}
