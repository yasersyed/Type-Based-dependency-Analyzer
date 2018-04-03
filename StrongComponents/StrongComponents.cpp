///////////////////////////////////////////////////////////////////
// StrongComponents.cpp - StrongComp Library                     //
// Ver 1.0                                                       //
// Application: Print Strong Components of each Node             //
// Platform:    MacBook Pro, Win 10 Education, Visual Studio 2015//
// Author:      Syed Yaser Ahmed				                 //
//              sysyed@syr.edu		                             //
///////////////////////////////////////////////////////////////////

#include "StrongComponents.h"
#include <iostream>
#include <unordered_map>

#ifdef DEBUG_SC
int main(void)
{

	StrongComp t;
	t.init();
	node a, b, c, d, e, f, g, h;
	a.name = "a";
	b.name = "b";
	c.name = "c";
	d.name = "d";
	e.name = "e";
	f.name = "f";
	g.name = "g";
	h.name = "h";
	a.adjlist.push_back(&e);
	b.adjlist.push_back(&a);
	c.adjlist.push_back(&b);
	c.adjlist.push_back(&d);
	d.adjlist.push_back(&c);
	e.adjlist.push_back(&b);
	f.adjlist.push_back(&b);
	f.adjlist.push_back(&e);
	f.adjlist.push_back(&g);
	g.adjlist.push_back(&c);
	g.adjlist.push_back(&f);
	h.adjlist.push_back(&d);
	h.adjlist.push_back(&g);
	h.adjlist.push_back(&h);
	std::vector<node*> v;
	v.push_back(&a); v.push_back(&b); v.push_back(&c); v.push_back(&d); v.push_back(&e); v.push_back(&f); v.push_back(&g); v.push_back(&h);
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i]->found == 0) {
			t.strongconnect(v[i]);
		}
	}
	return 0;
}
#endif