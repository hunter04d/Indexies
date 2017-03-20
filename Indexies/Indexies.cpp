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


	IndexTable a(3);
	a.Print();
	FunctionBool func({0,1,0,0,1,0,0,0});
	a.RemoveFromFunction(func, 1);
	a.Print();


	std::cout << "IndexTable for vars created";

	_getch();
}