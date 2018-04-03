///////////////////////////////////////////////////////////////////
// XMLclass.cpp - XMLclass Library				                 //
// Ver 1.0                                                       //
// Application: Contains Test Stub for NoSqlDb.h                 //
// Platform:    MacBook Pro, Win 10 Education, Visual Studio 2015//
// Author:      Syed Yaser Ahmed				                 //
//              sysyed@syr.edu		                             //
///////////////////////////////////////////////////////////////////
#include <iostream>

#ifdef DEBUG_XMLCLASS
int main()
{
	//Include XMLclass.h
	NoSqlDb<std::string> db;
	metadata<std::string> elem1;
	elem1.name = "element1";
	elem1.children = {};
	/*elem1.timeDate = "03/07/2017 2:00 PM";*/
	db.save(elem1.name, elem1);
	XMLclass xc;
	std::string xml = xc.toXml(db);
	std::cout << xml;

}
#endif // DEBUG_XMLCLASS