///////////////////////////////////////////////////////////////////
// StrongComponents.h - Contains class for Tarjan's Strong 		 //
// Component for graphs											 //
// Ver 1.0                                                       //
// Application: Print Strong Components of each Node             //
// Platform:    MacBook Pro, Win 10 Education, Visual Studio 2015//
// Author:      Syed Yaser Ahmed				                 //
//              sysyed@syr.edu		                             //
///////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This header contains class for Tarjan's Strongly connected algorithm derived from the data 
*	from Graph.h. The functions defined in this header are used for finding the strongly connected nodes of each
*	vertex in the graph created in Graph package.
*
*	class  functions
*  ---------------------------------
*	void init(); - Initialize the index
*	void strongconnect(node * nn); - Find strongly connected nodes of unvistied nodes
*	void executiveSC(unordered_map<string, vector<string>>); - 
*	Function for getting the vertex and edges which is received in the form of a map
*	from the built graph in Graph.h
*
*
*
* Maintenance History:
* --------------------
* Ver 1.0 : 07 Mar 2017
* - first release
*
*/
#pragma warning(disable : 4018)

#ifndef STC_H
#define STC_H
#undef min
#undef max
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <unordered_map>

class node
{
public:
	int index; 
	int LL;
	int found; 
	std::string name;
	std::vector<node> AdjacentNode;
};
class StrongComp {
public:
	void init();
	void strongconnect(node * nn);
	std::string executiveSC(std::unordered_map<std::string, std::vector<std::string>>);
private:
	int index;
	std::stack<node*> S;
	std::string xmlString;
};

inline void StrongComp::init()
{
	index = 1;
}
inline void StrongComp::strongconnect(node * nn)
{
	node next;
	nn->index = index;
	nn->LL = index;
	index++;
	S.push(nn);
	nn->found = 1;
	for (int i=0; i< nn->AdjacentNode.size();i++)
	{
		next = nn->AdjacentNode[i];
		if (next.found == 0) {
			strongconnect(&next);
			nn->LL = std::min(nn->LL, next.LL);
		}
		else if (next.found == 1) { 
			nn->LL = std::min(nn->LL, next.index);
		}
	}
	if (nn->LL == nn->index) {
		std::cout << "Strongly Connected Nodes--\n";
		xmlString += "\t <StrongComponents>";
		while (1) {
			node * temp = S.top();
			S.pop();
			temp->found = 2;
			std::cout << (temp->name).c_str() << "\n";
			xmlString += (temp->name).c_str();
			xmlString += "</StrongComponents>\n";
			if (temp == nn) break;
		}
	}
}
node b;
inline std::string StrongComp::executiveSC(std::unordered_map<std::string, std::vector<std::string>> mt1)
{
	std::cout << "\n Requirement 6 - Finding strong components in the dependency graph produced in previous requirement \n";
	std::cout << " -----------------------------------------------------------------------------------------------------\n\n";
	init();
	std::vector<node> v;
	for (std::unordered_map<std::string, std::vector<std::string>>::const_iterator it = mt1.begin();
		it != mt1.end(); ++it)
	{
		node a;
		a.name = (it->first).c_str();
		a.found = 0;
		a.index = 0;
		a.LL = 0;
		for (auto it1 : it->second)
		{
			b.name = it1;
			b.index = 0;
			b.found = 0;
			b.LL = 0;
			a.AdjacentNode.push_back(b);
			b.name = "";
		}
		v.push_back(a);
	}
	for (auto i : v)
	{
		xmlString += "<Component>\n";
		if (i.found == 0)
		{
			strongconnect(&i);
		}
		std::cout << "\n\n";
		xmlString += "</Component>\n";
	}
	return xmlString;
}
#endif