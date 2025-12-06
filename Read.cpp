#include "Read.h"

Read::Read(Point Lcorner, const string& var)
{
	this->varName = var;
	LeftCorner = Lcorner;
	pOutConn = NULL;	//No connectors yet
	UpdateStatementText();

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}
void Read::Draw(Output* pOut) const
{
	pOut->DrawInputStatement(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}
void Read::Save(ofstream& OutFile)
{
	// to be implemented 
	return;
}
void Read::Load(ifstream& InFile)
{
	// to be implemented
	return;
}
void Read::Edit()
{
	// to be implemented
	return;
}
Statement* Read::Simulate(Input* pIn, Output* pOut)
{
	pOut->PrintMessage("Enter the value for " + varName + ":");
	double value = pIn->GetValue(pOut);
	SetVar(varName, value);
	if (pOutConn != NULL)
	{
		return pOutConn->getDstStat();
	}
	else
	{
		return NULL;
	}
}

void Read::GenerateCode(ofstream& OutFile)
{
	// to be implemented
	return;
}
void Read::UpdateStatementText()
{
	Text = "Read " + varName;
}

bool Read::Validate(varinfo vars[], int& varcount, string& msg)
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

