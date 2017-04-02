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
#include "FunctionBool.h"
using std::vector;

int main()
{
	long long t0  = (long long)time(NULL);
	for(int i = 0 ; i < 10000; ++i)
	{
		std::cout << 4 << '\n' ;
	}
	long long t1 = (long long)time(NULL);
	std::cout << t1 - t0;

	_getch();
}
