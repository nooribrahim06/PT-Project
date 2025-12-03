#include "Condition.h"
#include <sstream>

Condition::Condition(Point C, string L, string R)
{
	// to be implemented 
	int W = UI.ASSGN_WDTH;
	int H = UI.ASSGN_HI;
	Center = C;
	LHS = L;
	RHS = R;
	UpdateStatementText();
	Inlet.x = Center.x;
	Inlet.y = Center.y - H / 2;
	TrueOutlet.x = Center.x + W/2;
	FalseOutlet.x = Center.x - W / 2;
	TrueOutlet.y = Center.y;
	FalseOutlet.y = Center.y;
	pTrueOutConn = NULL;	//No connectors yet
	pFalseOutConn = NULL;	//No connectors yet
}
void Condition::setLHS(const string& L)
{
	// to be implemented 
	LHS = L;
	UpdateStatementText();
}
void Condition::setRHS(const string& R)
{
	// to be implemented 
	RHS = R;
	UpdateStatementText();
}
void Condition::Draw(Output* pOut) const
{
	// to be implemented 
	pOut->DrawCondStatement(Center, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}
void Condition::Save(ofstream& OutFile)
{
	// to be implemented 
	return;
}
void Condition::Load(ifstream& InFile)
{
	// to be implemented
	return;
}
void Condition::Edit()
{
	return;
}
void Condition::Simulate()
{
	return;
}
void Condition::GenerateCode(ofstream& OutFile)
{
	return;
}
void Condition::UpdateStatementText()
{
	// to be implemented 
	ostringstream T;
	T << LHS << " " << RHS;
	Text = T.str();
}