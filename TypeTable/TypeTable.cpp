///////////////////////////////////////////////////////////////////
// NoSqlDb.cpp - TypeTable Library			                     //
// Ver 1.0                                                       //
// Application: Contains Test Stub for TypeTable.h               //
// Platform:    MacBook Pro, Win 10 Education, Visual Studio 2015//
// Author:      Syed Yaser Ahmed				                 //
//              sysyed@syr.edu		                             //
///////////////////////////////////////////////////////////////////

#include "TypeTable.h"

#ifdef DEBUG_TYPETABLE
int main()
{
	TypeTable tb;
	tb.addType("abc", "type1", "path1");
	tb.addType("def", "type2", "path2");
	tb.addType("ghi", "type3", "path3");
	tb.addType("jkl", "type4", "path4");
	tb.addType("mno", "type5", "path5");
	tb.displayMap();
}
#endif // DEBUG