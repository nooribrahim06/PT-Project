#include "Write.h"
Write::Write(Point Lcorner,string& variable)
{
	var = variable;
	LeftCorner = Lcorner;
	pOutConn = NULL;	//No connectors yet
	UpdateStatementText();
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}
void Write::Draw(Output* pOut) const {
	pOut->DrawOutputStatement(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}
void Write::Save(ofstream& OutFile)
{
	return;
}
void Write::Load(ifstream& InFile)
{
	return;
}
void Write::Edit()
{
	// to be implemented
	return;
}
void Write::Simulate()
{
	return;
}

void Write::GenerateCode(ofstream& OutFile)
{
	// to be implemented
	return;
}

bool Write::Validate(varinfo vars[], int& varcount, string& msg)
{
	if (var.empty()) {
		msg = "Write statment doesn't have an expresson";
		return false;
	}
	OpType T = ValueOrVariable(var);
	if (T == VARIABLE_OP)
	{
		int idx = Findvarindex(var, vars, varcount);
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
	{
		msg = "Write statement has invalid expression '" + var + "' ";
		return false;
	}
	return true;
}
void Write::UpdateStatementText()
{
	Text = "Write " + var;
}
