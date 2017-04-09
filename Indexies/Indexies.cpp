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
#include "MinimizedManager.h"
auto a = "0100111111010111111010111101101010";
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
	auto all_cases = b.ReturnRest();
	for (auto& element : all_cases)
	{	std::cout << element << '\n';	}
	std::cout << std::count(all_cases.at(all_cases.size() - 1).cbegin(), all_cases.at(all_cases.size() - 1).cend(), 'v') + 1 << '\n';
	std::cout << all_cases.size();
	std::cout << '\n';
	std::cout << '\n';
	std::cout << '\n';
	std::cout << '\n';
	std::cout << '\n';
	MinimizedManager m(all_cases, b.ReturnCore());
	auto all_minimizations = m.GetAll();
	for(const auto& x : all_minimizations)
	{
		std::cout << x << '\n';
	}
	std::cout << '\n';
	std::cout << '\n';
	std::cout << '\n';
	std::cout << '\n';
	std::cout << '\n';
	for (const auto& x : all_minimizations)
	{
		auto x12 = Namefy(x);
		std::cout << x12[0] << '\n' << x12[1] << '\n';
	}
	system("pause");

}
