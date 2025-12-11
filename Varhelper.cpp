#include "Varhelper.h"
#include "Statements/Statement.h"
Varhelper::Varhelper()
{
	varcount = 0;
	for (int i = 0; i < Maxvars; i++)
	{
		vars[i].name = "";
		vars[i].declared = false;
		vars[i].initialized = false;
	}
}

int Varhelper::Findindex(const string& name) const
{
	for (int i = 0; i < varcount; i++)
	{
		if (vars[i].name == name)
		{
			return i;
		}
	}
	return -1;
}

void Varhelper::declare(const string& name)
{
	int idx = Findindex(name);


	if (idx == -1)
	{
		if (varcount < Maxvars) {
			vars[varcount].name = name;
			vars[varcount].declared = true;
			vars[varcount].initialized = false;
			varcount++;
		}
	}
	else {
		vars[idx].declared = true;
	}
}

void Varhelper::Markintialized(const string& name)
{
	int idx = Findindex(name);
	if (idx != -1)
	{
		vars[idx].initialized = true;
	}
}

bool Varhelper::tocheck(const string& name, bool checkintial, string& msg) const
{
	int idx = Findindex(name);

	if (idx == -1 || !vars[idx].declared) {
		msg = "Variable " + name + " used without declaration.";
		return false;
	}
	if (checkintial && !vars[idx].initialized) {
		msg = "Variable " + name + " used without Initialization.";
		return false;

	}
	return true;
}