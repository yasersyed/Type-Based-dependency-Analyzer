///////////////////////////////////////////////////////////////////
// TypeAnalysis.h									 			 //
//																 //
// Package for Analysing types from list of files				 //
// Ver 1.0                                                       //
// Application: can store a key and a pair of string values      //
// Platform:    MacBook Pro, Win 10 Education, Visual Studio 2015//
// Author:      Syed Yaser Ahmed				                 //
//              sysyed@syr.edu		                             //
///////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This header contains class for collecting type information from files and storing them in ASTNode
* from ASTNode->pRoot we collect only the necessary information and store in typetable
*
*	class  functions
*  ---------------------------------
*	std::unordered_map<std::string,_pair> doTypeAnal(); - makes use of ASTRef and DFS for searching and adding values to type table
*	void DFS(ASTNode* pNode); - function for recursively searching depth first through Abstract syntax tree
*	std::string setnSpace(std::string ns); - function for returning namespace string
*
*	Build Process:
*	==============
*	Required files
*	- AbstrSynTree.h, AbstrSynTree.cpp, TypeTable.h
*	- ActionsAndRules.h, ConfigureParser.h, ScopeStack.h
*	- Scanner.h
*
*	Build command
*	- devenv Project2.sln
*
* Maintenance History:
* --------------------
* Ver 1.0 : 07 Mar 2017
* - first release
*
*/

#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include "../TypeTable/TypeTable.h"
#include "../CodeAnalyzer/ConfigureParser.h"
#include "../CodeAnalyzer/ActionsAndRules.h"


namespace CodeAnalysis
{
	class TypeAnalysis {
	public:
		using SPtr = std::shared_ptr<ASTNode*>;
		TypeAnalysis();
		std::unordered_map<std::string,_pair> doTypeAnal();
		std::string setnSpace(std::string ns);
	private:
		void DFS(ASTNode* pNode);
		AbstrSynTree& ASTref_;
		ScopeStack<ASTNode*> scopeStack_;
		Scanner::Toker& toker_;
		TypeTable *tt = new TypeTable();
		
	};
	inline TypeAnalysis::TypeAnalysis() :
		ASTref_(Repository::getInstance()->AST()),
		scopeStack_(Repository::getInstance()->scopeStack()),
		toker_(*(Repository::getInstance()->Toker()))
	{
		/*std::function<void()> test = [] { int x; };*/  
	}                                              

	inline bool doDisplay(ASTNode* pNode)
	{
		static std::string toDisplay[] = {
			"function", "lambda", "class", "struct", "enum", "alias", "typedef","namespace"
		};
		for (std::string type : toDisplay)
		{
			if (pNode->type_ == type)
				return true;
		}
		return false;
	}
	inline void TypeAnalysis::DFS(ASTNode* pNode)
	{
		static std::string path = "";
		static std::string nspace = "";
		if (pNode->path_ != path)
			path = pNode->path_;
		if (pNode->type_ == "namespace")
			nspace = pNode->name_;
		if (doDisplay(pNode))
		{
			if(pNode->type_ != "control" || pNode->name_ !="Global Namespace" || pNode->name_ !="main")
				tt->addType(path, nspace, pNode->name_);
		}
		for (auto pChild : pNode->children_)
			DFS(pChild);
	}
	inline std::string TypeAnalysis::setnSpace(std::string ns)
	{
		return ns;
	}
	inline std::unordered_map<std::string,_pair> TypeAnalysis::doTypeAnal()
	{
		std::cout << "\n Requirement 4 : TypeAnalysis package that identifies all of the types defined in a specified file \n";
		std::cout << "---------------------------------------------------------------------------------------------------  \n";
		std::cout << "\n  scanning AST and displaying type definitions, global function definitions, global data definitions";
		std::cout << "\n --------------------------------------------------------------------------------------------------- \n";
		ASTNode* pRoot = ASTref_.root();
		DFS(pRoot);
		std::cout <<"\n Printing TypeTable: \n";
		tt->displayMap();
		return tt->returnMap();
	}
}
