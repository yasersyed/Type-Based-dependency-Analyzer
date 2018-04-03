///////////////////////////////////////////////////////////////////
// DependencyAnalyzer.h									 		 //
//																 //
// Package for Analysing Dependency from a list of files		 //
// Ver 1.0                                                       //
// Application: can store a key and a pair of string values      //
// Platform:    MacBook Pro, Win 10 Education, Visual Studio 2015//
// Author:      Syed Yaser Ahmed				                 //
//              sysyed@syr.edu		                             //
///////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This header contains class for comparing tokens from given files and matching them in Type table
* to get dependencies of given files
*
*	class  functions
*  ---------------------------------
*	NoSqlDb<string> findDependency(unordered_map<string, _pair>,vector<string>) -
*
*	Uses Abstract syntax tree and Scanner to get the tokens in each line of each file provided in the 1st argument.
*   The found tokens are compared to the type table map provided as first argument and builds a dependency Database
*   using NoSqlDb with dependencies stored as children.
*
*	Build Process:
*	==============
*	Required files
*	- AbstrSynTree.h, AbstrSynTree.cpp, TypeTable.h
*	- ActionsAndRules.h, ConfigureParser.h, NoSqlDb.h
*	- XMLClass.h
*
*	Build commands
*	- devenv Project2.sln
*
* Maintenance History:
* --------------------
* Ver 1.0 : 07 Mar 2017
* - first release
*
*/

#pragma once
#include<iostream>
#include<unordered_map>
#include<vector>
#include<sstream>
#include"../TypeTable/TypeTable.h"
#include "../CodeAnalyzer/AbstrSynTree.h"
#include "../CodeAnalyzer/ActionsAndRules.h"
#include "../CodeAnalyzer/ConfigureParser.h"
#include "../NoSqlDb/NoSqlDb.h"
#include "../NoSqlDb/XMLClass.h"



using StrData = std::string;
using Key = NoSqlDb<StrData>::Key;
using Keys = NoSqlDb<StrData>::Keys;

using namespace Scanner;
namespace CodeAnalysis {
	class DependencyAnalyzer
	{
	public:
		DependencyAnalyzer();
		NoSqlDb<std::string> findDependency(std::unordered_map< std::string, _pair>,std::vector<std::string>,std::string);
		void storeInXML(NoSqlDb<std::string> d, std::string s);
	private:
		std::unordered_map<std::string,std::string> dep;
		std::vector<std::pair<std::string,std::string>> deps;
		std::unordered_map<std::string, std::vector<std::string>> deps2;
		AbstrSynTree& ASTref_;
		ScopeStack<ASTNode*> scopeStack_;
		Scanner::Toker& toker_;
	};
	inline DependencyAnalyzer::DependencyAnalyzer() :
		ASTref_(Repository::getInstance()->AST()),
		scopeStack_(Repository::getInstance()->scopeStack()),
		toker_(*(Repository::getInstance()->Toker()))
	{
		/*std::function<void()> test = [] { int x; };*/
	}
	inline NoSqlDb<std::string> DependencyAnalyzer::findDependency(std::unordered_map< std::string,_pair> tab, std::vector<std::string> ve,std::string output)
	{
		std::cout << "\n\n Requirement 5 - DependencyAnalysis package that identifies all of the dependencies between files in a specified file collection \n";
		std::cout << "------------------------------------------------------------------------------------------------------------------------------------ \n";
		NoSqlDb<std::string> depDB;
		for (std::string fileSpec : ve) {
			try
			{
				metadata<std::string> element;
				std::ifstream in(fileSpec);
				if (!in.good())
					std::cout << "\n  can't open " << fileSpec << "\n\n"; {
					Toker toker;//toker.returnComments();
					toker.attach(&in);
					do {
						std::string tok = toker.getTok();
						auto it = (tab.find(tok));
						if (it != tab.end()){
							if ((fileSpec != tab[tok].second) && (std::find(deps.begin(), deps.end(), make_pair(fileSpec, tab[tok].second)) == deps.end())){
								element.name = fileSpec;
								element.children.push_back(tab[tok].second);
								deps.push_back(make_pair(fileSpec, tab[tok].second));
							}
							if(fileSpec == tab["Logging"].second && (std::find(deps.begin(), deps.end(), make_pair(fileSpec, tab[tok].second)) == deps.end())){
								element.name = fileSpec;
								element.children = {};
								deps.push_back(make_pair(fileSpec, tab[tok].second));
							}
						}
					} while (in.good());
					depDB.save(element.name, element);
				}
			}
			catch (std::logic_error& ex) {
				std::cout << "\n  " << ex.what();
			}
		}
		depDB.remove("");
		depDB.cleanDB(depDB);
		storeInXML(depDB, output);
		return depDB;
	}
	inline void DependencyAnalyzer::storeInXML(NoSqlDb<std::string> depDB, std::string output)
	{
		XMLclass xc;
		try {
			std::string xml = xc.toXml(depDB);
			std::ofstream file(output);
			file << xml;
			std::cout << "\n Storing Database in " << output << " File \n";
			file.close();
		}
		catch (std::exception ex) { std::cout << ex.what(); }
	}
}