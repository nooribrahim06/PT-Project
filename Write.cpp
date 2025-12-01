#include "Write.h"
Write::Write(string& variable)
{
}
void Write::Draw(Output* pOut) const {
}
void Write::Save(ofstream& OutFile)
{
}
void Write::Load(ifstream& InFile)
{
}
void Write::Simulate()
{
}

void Write::GenerateCode(ofstream& OutFile)
{
	// to be implemented
}

bool Write::checkvar(varinfo vars[], int& varcount, string& msg)
{
	if (var.empty()){
		msg = "Write statment doesn't have an expresson";
	return false;
}
	OpType T = ValueOrVariable(var);
	if (T == VARIABLE_OP)
	{
		int idx= Findvarindex(var, vars, varcount);
		if (idx == -1 || !vars[idx].declared) {
			msg = "Variable " + var + " used without declaration.";
			return false;
		}
		if (!vars[idx].initialized) {
						msg = "Variable " + var + " used without initialization.";
						return false;
		}
	}
	else if (T == INVALID_OP)
	{msg = "Write statement has invalid expression '"  + var + "' ";
	return false;
	}
	return true;
}
