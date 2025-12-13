#include "Declare.h"
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

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
	OutFile << "DCLR	" << GetstatementID() << "	" << LeftCorner.x << "	" << LeftCorner.y << "	" << var << endl;
	return;
}
void Declare::Load(ifstream& InFile)
{
	
	InFile >> statementID >> LeftCorner.x >> LeftCorner.y >> var;
	
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
	UpdateStatementText();
	return;
}
void Declare::Edit()
{
	// to be implemented
	return;
}
Statement* Declare::Simulate(Input* pIn, Output* pOut)
{
	 Statement ::SetVar(var, 0);
	 Connector* pOutConn = GetOutConnector();
	if (pOutConn != NULL)
	{
		return pOutConn->getDstStat();
	}
	else
	{
		return NULL;
	}
}
	



void Declare::GenerateCode(ofstream& OutFile)
{
	OutFile << "double " << var << ";\n";
}
bool Declare::IsPointInside(Point P) const
{
	bool x_inside = (P.x >= LeftCorner.x) && (P.x <= LeftCorner.x + UI.ASSGN_WDTH);
	bool y_inside = (P.y >= LeftCorner.y) && (P.y <= LeftCorner.y + UI.ASSGN_HI);
	return (x_inside && y_inside);
}
Point Declare::GetOutletPoint() const
{
	return Outlet;
}
Point Declare::GetInletPoint() const
{
	return Inlet;
}

Connector* Declare::GetOutConnector() const
{
	return pOutConn;
}

void Declare::SetOutconnector(Connector* C)
{
	pOutConn = C;
}

bool Declare::Validate(varinfo vars[], int& varcount, string& msg)
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
