#pragma once
#include "Statements/Statement.h"
class Varhelper
{ 
	static const int Maxvars = 200;
	varinfo vars[Maxvars];
	int varcount;
public:
	Varhelper();
	int Findindex(const string& name)const;
	void declare(const string& name);
	void Markintialized(const string& name);
	bool tocheck(const string& name, bool checkintial, string& msg) const;
};

