///////////////////////////////////////////////////////////////////
// NoSqlDb.cpp - NoSqlDb database Library                        //
// Ver 1.0                                                       //
// Application: Contains Test Stub for NoSqlDb.h                 //
// Platform:    MacBook Pro, Win 10 Education, Visual Studio 2015//
// Author:      Syed Yaser Ahmed				                 //
//              sysyed@syr.edu		                             //
///////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS

#include "NoSqlDb.h"
#include "XMLclass.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <chrono>
#include <thread>
#include <future>

using Data = std::string;
using Key = NoSqlDb<std::string>::Key;
using Keys = NoSqlDb<std::string>::Keys;

std::string getLocaltime() //gets current time as string
{
	std::time_t _tm = std::time(NULL);
	struct tm * curtime = std::localtime(&_tm);
	char buffer[32];
	std::strftime(buffer, 32, "%d:%m:%Y %H:%M:%S", curtime); // convert time_t to string for storage
	return buffer;
}

#ifdef  TEST_NOSQLDB



int main()
{
	NoSqlDb<std::string> db;
	Element<std::string> elem1, elem2;
	elem1.name = "Test1";
	elem1.children = {"Test2"};
	elem2.name = "Test2";
	db.save(elem1.name, elem1);
	db.save(elem2.name, elem2);
	db.display(db);
}

#endif //  TEST_NOSQLDB