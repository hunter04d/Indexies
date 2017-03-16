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
#include "FunctionBool.h"
using std::vector;
int main()
{
/*
	std::string a = "cd";
	std::string b = "abc";
	std::cout << utility::hasString(a, b);
*/

	IndexTable a(4);
	FunctionBool func({ 0,1,0,0,1,1,0,0,1,1,1,0,0,1,0,0 });
	std::string DDNF = func.DDNF();
	a.RemoveFromFunction(func, 1);

	//PrintTable(func);
	a.RemoveRemoved();
	a.PrintNames();
	a.PrintFile();
	std::cout << std::endl;
	a.Print();
	a.Consume();
	a.PrintNames();
	a.PrintFile();
	std::cout << std::endl;
	a.Print();

	_getch();
}