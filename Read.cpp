#include "Read.h"

Read::Read(const string& var)
{
}
void Read::Draw(Output* pOut) const
{
}
void Read::Save(ofstream& OutFile)
{
	// to be implemented 
}
void Read::Load(ifstream& InFile)
{
	// to be implemented
}
void Read::Edit()
{
	// to be implemented
}
void Read::Simulate()
{
	// 
}

void Read::GenerateCode(ofstream& OutFile)
{
	// to be implemented
}

bool Read::checkvar(varinfo vars[], int& varcount, string& msg)
{
	if (varName.empty()) {
		msg = "The variable name in Read statement is empty";
		return false;
	}
	if(!IsVariable(varName)) {
		msg = "Read statement variable '" + varName + "' is not a valid variable name.";
		return false;
	}
	int idx = Findvarindex(varName, vars, varcount);
	if (idx == -1||!vars[idx].declared) {
		msg= "Variable " + varName + " used without declaration.";
		return false;
	}
	else {
		vars[idx].initialized = true;
		return true;
		
	}
}

