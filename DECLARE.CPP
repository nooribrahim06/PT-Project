#include "Declare.h"
#include <sstream>



Declare::Declare(Point Lcorner, string& V)
{
	// initially set the declare width and height to be the same as assignment statement
	LeftCorner = Lcorner;
	var = V;
	UpdateStatementText();
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
	pOutConn = NULL;	//No connectors yet
}
void Declare::Draw(Output* pOut) const {
	// void Output::DrawDeclareStatement(Point left, int width, int height, string Text, bool Selected)
	pOut->DrawDeclareStatement(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}
void Declare::Save(ofstream& OutFile)
{
	// to be implemented 
}
void Declare::Load(ifstream& InFile)
{
	// to be implemented
}
void Declare::Edit()
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
	// 
}
void Declare::UpdateStatementText()
{
	ostringstream T;
	T << "Declare " << var;
	Text = T.str();
}
