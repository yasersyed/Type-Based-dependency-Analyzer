///////////////////////////////////////////////////////////////////
// TypeTable.h - Contains class for Storing analysis data 		 //
//																 //
// Ver 1.0                                                       //
// Application: can store a key and a pair of string values      //
// Platform:    MacBook Pro, Win 10 Education, Visual Studio 2015//
// Author:      Syed Yaser Ahmed				                 //
//              sysyed@syr.edu		                             //
///////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This header contains class for storing type analysis data in a map for easy 
*	dependency analysis
*
*	class  functions
*  ---------------------------------
*	void addType(std::string,std::string,std::string); - will add, 1st string as key, 2nd string 
*														 as namespace part of pair and 
*														 3rd string as path part of pair
*	std::unordered_map<std::string,_pair> returnMap(); - will return the typetable, in case we need it
*
*	void displayMap(); - Function for displaying the typetable
*
*
*
* Maintenance History:
* --------------------
* Ver 1.0 : 07 Mar 2017
* - first release
*
*/

#pragma once
#include <unordered_map>
#include <iostream>
#include <string>
#include <iomanip>

using _pair = std::pair<std::string, std::string>;

//Struct for hash table in case an unordered map of pair_ and string is used
struct SimpleHash {
	size_t operator()(const std::pair < std::string, std::string > & p) const {
		auto h1 = std::hash<std::string>{}(p.first);
		auto h2 = std::hash<std::string>{}(p.second);
		return h1^h2;
	}
};
class TypeTable 
{
public:
	TypeTable(){}
	~TypeTable(){}
	void addType(std::string,std::string,std::string);
	std::unordered_map<std::string,_pair> returnMap();
	void displayMap();
private:
	std::unordered_map<std::string,_pair> table;
};

void TypeTable::addType(std::string filename, std::string ftype, std::string nspace)
{
	std::pair<std::string, std::string> pair = std::make_pair(ftype,filename);
	table.emplace(nspace,pair);
}
inline std::unordered_map<std::string,_pair> TypeTable::returnMap()
{
	return table;
}
inline void TypeTable::displayMap()
{
	std::cout << std::setw(35) << std::left << "Name"
		<< std::setw(15) << "NameSpace" << "\t"
		<< std::setw(10) << "FilePath" << "\n";
	for (std::unordered_map<std::string,_pair>::const_iterator it = table.begin();
		it != table.end(); ++it)
	{
		if (it->first != "Global Namespace")
		{
			std::cout << std::setw(35) << std::left << it->first
				<< std::setw(15) << it->second.first << "\t"
				<< std::setw(10) << it->second.second << "\n";
		}
	}
}
