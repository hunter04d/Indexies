// Indexies.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <bitset>
#include <vector>
#include <conio.h>
#include "VarTable.h"
#include <exception>
#include "PrintTable .h"
#include "UtilityFunc.h"
#include "IndexTable.h"
#include "CoreTable.h"
#include "FunctionBool.h"
using std::vector;

int main()
{
	//FunctionBool func = { 0,1,0,0,0,1,0,0,0,1,0,1,1,1,0,1 };
	FunctionBool func = { 1,0,1,0,1,0,0,0,0,0,0,0,1,1,0,1 };
	IndexTable a(func.numberOfvars);
	a.RemoveFromFunction(func);
	a.PrintNames();
	std::cout << '\n';
	a.Print();
	std::cout << '\n';
	CoreTable b(a.GetTermsInCoreForm(), func);
	b.Print();
	b.SetIsCrossed_MinTermTags_and_DeletedCellTags();
	b.Print();
	system("pause");
}
