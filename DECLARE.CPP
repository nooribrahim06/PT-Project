#include "Declare.h"

Declare::Declare(string& var)
{
	// implement later
}
void Declare::Draw(Output* pOut) const {

}
void Declare::Save(ofstream& OutFile)
{
	// to be implemented 
}
void Declare::Load(ifstream& InFile)
{
	// to be implemented
}
void Declare::Simulate()
{
	// add var to the context's variable table with default value

}

void Declare::GenerateCode(ofstream& OutFile)
{
	// TO be implemented

}

bool Declare::checkvar(varinfo vars[], int& varcount, string& msg)
{
	if (var.empty()) {
		msg = "Empty variable name in declaration";
		return false;
	}
	if (!IsVariable(var)) {
		msg = "Invalid variable name in declaration: '" + var + "' ";
		return false;
	}
	int index = Findvarindex(var, vars, varcount);
	if (index == -1)
	{
		index = varcount++;
		vars[index].name = var;
		vars[index].declared = true;
		vars[index].initialized = false;
	}
	else {
	vars[index].declared = true;
}
	return true;
}
