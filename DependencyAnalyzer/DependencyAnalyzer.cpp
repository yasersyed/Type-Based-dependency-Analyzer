///////////////////////////////////////////////////////////////////
// DependencyAnalyzer.cpp - DependencyAnalyzer Library	         //
// Ver 1.0                                                       //
// Application: Contains Test Stub for DependencyAnalyzer.h      //
// Platform:    MacBook Pro, Win 10 Education, Visual Studio 2015//
// Author:      Syed Yaser Ahmed				                 //
//              sysyed@syr.edu		                             //
///////////////////////////////////////////////////////////////////


#include "DependencyAnalyzer.h"
#include <iostream>
#include <conio.h>
#include <iomanip>
#include "../NoSqlDb/NoSqlDb.h"

#ifdef TEST_DEPENDENCY
int main()
{

	CodeAnalysis::DependencyAnalyzer da;
	std::unordered_map<std::string, _pair> maTable;
	maTable.emplace("test", std::make_pair("test1", "test2"));
	maTable.emplace("test8", std::make_pair("test3", "test4"));
	maTable.emplace("test9", std::make_pair("test5", "test6"));
	std::vector<std::string> veC;
	veC.push_back("test1");
	veC.push_back("test2");
	veC.push_back("test3");
	NoSqlDb<std::string> db=da.findDependency(maTable,veC);
}
#endif