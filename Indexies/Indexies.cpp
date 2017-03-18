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


	IndexTable a(4);
	a.PrintNames();
	std::cout << std::endl;
	a.Print();
	FunctionBool func({ 0,1,0,0,1,1,0,0,1,1,1,0,0,1,0,0 });

	a.Consume();
	a.PrintNames();
	std::cout << std::endl;
	a.Print();


	_getch();
}