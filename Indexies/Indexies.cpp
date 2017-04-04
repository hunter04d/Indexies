// Indexies.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "PrintTable .h"
#include "UtilityFunc.h"
#include "IndexTable.h"
#include "CoreTable.h"
#include "FunctionBool.h"

int main()
{
	//FunctionBool func = { 0,1,0,0,0,1,0,0,0,1,0,1,1,1,0,1 };
	FunctionBool func("0100111111010111111010111101101010");
	IndexTable a(func.numberOfvars);
	a.RemoveFromFunction(func);
	a.PrintNames();
	std::cout << '\n';
	a.Print();
	std::cout << '\n';
	CoreTable b(a.GetTermsInCoreTableForm(), func);
	b.Print();
	b.GetCore();
	b.Print();
	system("pause");

}
