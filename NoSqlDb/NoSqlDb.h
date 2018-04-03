///////////////////////////////////////////////////////////////////
// NoSqlDb.h - Contains classes for metadata, NoSqlDb			 //
// Widgets and Widget Persistance Interface						 //
// Ver 1.0                                                       //
// Application: Storing data in a NoSqlDb                        //
// Platform:    MacBook Pro, Win 10 Education, Visual Studio 2015//
// Author:      Syed Yaser Ahmed				                 //
//              sysyed@syr.edu		                             //
///////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This header contains classes for creating Database Elements and Databases themselves.
* metadata<Data> class contains definition for the datatype and functions for displaying metadata of any key
* NoSqlDB<Data> class contains definitions for storing database and deleting keys
* Widget class contains declarations for Properties which can be used instead of Data property in metadata
*
*
* The functions defined in this header are used for creating elements and storing in database
* by the TestExecutive.cpp
*	class metadata<Data> functions
*  ---------------------------------
*   std::string metadata<Data>::show() //To display an element in Database
*   metadata<Data> metadata<Data>::returns() // To get metadata and data from an element used by DBQuery.h
*
*	class NoSqlDb<Data> functions
*   ------------------------------
*   typename NoSqlDb<Data>::Keys NoSqlDb<Data>::keys() //To get all keys from a database
*   bool NoSqlDb<Data>::save(Key key, metadata<Data> elem) //Saving an element with its key in unordered map
*   void NoSqlDb<Data>::display(NoSqlDb<Data> db) //Displaying entire database
*   bool NoSqlDb<Data>::editDB1(Key key, metadata<Data> db) //For editing an element
*   void NoSqlDb<Data>::remove(Key key) //To remove a key, value pair from database
*   metadata<Data> NoSqlDb<Data>::value(Key key) //To get the elements of any given key
*   size_t NoSqlDb<Data>::count() //Used to get size of database
*
*	class WidgetWrapper functions
* --------------------------------
*   inline WidgetWrapper::Xml WidgetWrapper::savew() //For persisting widget in an xml string
*   inline void WidgetWrapper::restorew(const Xml& xml) //For restoring database from xml string
*
*
* Required Files:
* ---------------
*   - Convert.h, Convert.cpp
*	- Properties.h, Properties.cpp
*	- XMLDocument.h, XMLDocument.cpp
*   - XMLElement.h, XMLElement.cpp
*
*
* Maintenance History:
* --------------------
* Ver 1.0 : 07 Feb 2017
* - first release
*
*/

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <unordered_map>
#include <iomanip>
#include <sstream>
#include "../Convert/Convert.h"
#include "../Properties/Properties.h"
#include "../XMLDocument/XMLDocument.h"
#include "../XMLDocument/XMLElement.h"

using SPtr = std::shared_ptr<XmlProcessing::AbstractXmlElement>;

template <typename Data>
class metadata {
public:
	using Name = std::string;
	using Children = std::vector<std::string>;

	std::string name;
	std::vector<std::string> children;
	std::string show();
	metadata<Data> metadata<Data>::returns();
	metadata<Data> metadata<Data>::editele(metadata<Data>);
};
template <typename Data>
std::string metadata<Data>::show()
{
	std::ostringstream out;
	out.setf(std::ios::adjustfield, std::ios::left);
	out << "\n    " << std::setw(8) << "name" << " : " << name;
	//out << "\n    " << std::setw(8) << "timeDate" << " : " << timeDate;
	out << "\n    " << std::setw(8) << "Children" << " : ";
	std::vector<std::string> newV = children;
	for (std::vector<std::string>::const_iterator i = newV.begin(); i != newV.end(); ++i)
		out << *i << "\n\t       ";
	out << "\n";
	return out.str();
}
template <typename Data>
metadata<Data> metadata<Data>::returns() {
	metadata<Data> m;
	m.name = name;
	//m.timeDate = timeDate;
	m.children = children;
	return m;
}
template<typename Data>
inline metadata<Data> metadata<Data>::editele(metadata<Data> e)
{
	metadata<Data> e1;
	e1.name = e.name;
	e1.children = e.children;
	return e1;
}
template<typename Data>
class NoSqlDb
{
public:
	using Key = std::string;
	using Keys = std::vector<Key>;
	Keys keys();
	bool save(Key key, metadata<Data> elem);
	bool editDB1(Key key, metadata<Data> elem);
	void display(NoSqlDb<Data>);
	void remove(Key key);
	void cleanDB(NoSqlDb<Data>);
	metadata<Data> value(Key key);
	size_t count();
private:
	using Item = std::pair<Key, metadata<Data>>;
	std::unordered_map<Key, metadata<Data>> store;
};
template<typename Data>
typename NoSqlDb<Data>::Keys NoSqlDb<Data>::keys()
{
	Keys keys;
	for (Item item : store)
	{
		keys.push_back(item.first);
	}
	return keys;
}
template<typename Data>
bool NoSqlDb<Data>::save(Key key, metadata<Data> elem)
{
	if (store.find(key) != store.end())
		return false;
	store[key] = elem;
	return true;
}
template<typename Data>
void NoSqlDb<Data>::display(NoSqlDb<Data> db)
{
	Keys ki = db.keys();
	for (Key k : ki)
	{
		std::cout << db.value(k).show();
	}
}
template<typename Data>
bool NoSqlDb<Data>::editDB1(Key key, metadata<Data> element)
{
	if (store.find(key) != store.end())
	{
		store[key] = element;
		return true;
	}
	else
		return false;
}
template<typename Data>
void NoSqlDb<Data>::remove(Key key)
{
	try {
		store.erase(key);//Add delete children to this
	}
	catch (std::exception ex)
	{
		std::cout << "Key not found";
	}
}

template<typename Data>
inline void NoSqlDb<Data>::cleanDB(NoSqlDb<Data> db)
{
	Keys k = db.keys();
	std::vector<std::pair<std::string, std::string>> vec;
	for (Key ki : k)
	{
		metadata<std::string> e = db.value(ki).returns();
		for (auto it : e.children)
		{
			metadata<std::string> e1 = db.value(it).returns();
			for (auto it1 : e1.children)
			{
				if (it1 == ki)
					vec.push_back(make_pair(it1, e1.name));
			}
		}
	}
	for (size_t it=0; it<vec.size();++it)
	{
		metadata<std::string> elem;
		elem = db.value(vec[it].first).returns();
		elem.children.erase(std::remove(elem.children.begin(), elem.children.end(), vec[it].second), elem.children.end());
		db.editDB1(elem.name, elem);
	}
	db.display(db);
}

template<typename Data>
metadata<Data> NoSqlDb<Data>::value(Key key)
{
	if (store.find(key) != store.end())
		return store[key];
	return metadata<Data>();
}

template<typename Data>
size_t NoSqlDb<Data>::count()
{
	return store.size();
}
