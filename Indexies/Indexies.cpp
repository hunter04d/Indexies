// Indexies.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <bitset>
#include <vector>
#include <conio.h>
#include "VarTable.h"
#include "PrintTable .h"
#include "UtilityFunc.h"
#include "IndexTable.h"
using std::vector;
int main()
{
	IndexTable a(4);
	vector<bool> func = { 0,1,0,0,1,1,0,0,1,1,1,0,0,1,0,0 };
	std::cout << func.size() << std::endl;
	for (int i = 0; i < func.size(); ++i)
	{
		if (!func.at(i))
		{
			a.RemoveRow(i);
		}
	}
	PrintTable(func);
	a.RemoveRemoved();
	a.PrintNames();
	a.PrintFile();
	std::cout << std::endl;
	a.Print();

	_getch();
}