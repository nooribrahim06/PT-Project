#include "Read.h"
#include <iostream>
#include <fstream>
#include "..\GUI\UI_Info.h"
using namespace std;
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

void Read::Move(const Point& P)
{
	LeftCorner = P;
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}
Statement* Read::Clone() const {
	Read* copy = new Read(*this);
	return copy;
}
void Read::Save(ofstream& OutFile)
{
	OutFile << "READ	" << GetstatementID() << "	" << LeftCorner.x << "	" << LeftCorner.y << "	" << varName << endl;
	return;
}
void Read::Load(ifstream& InFile)
{
	int id;
	InFile >> id >> LeftCorner.x >> LeftCorner.y >> varName;
	statementID = id;
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
	UpdateStatementText();
	// to be implemented
	return;
}
void Read::Edit(const string& varName)
{
	// to be implemented
	this->varName = varName;
	UpdateStatementText();	
	return;
}
Statement* Read::Simulate(Input* pIn, Output* pOut)
{
	pOut->PrintMessage("Enter the value for " + varName + ":");
	double value = pIn->GetValue(pOut);
	 Statement::SetVar(varName, value);
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

void Read::GenerateCode(ofstream& OutFile)
{
	OutFile << "cin >> " << varName << ";\n";
}
Point Read::GetOutletPoint() const
{
	return Outlet;
}
Point Read::GetInletPoint() const
{
	return Inlet;
}
Connector* Read::GetOutConnector() const
{
	return pOutConn;
}
void Read::SetOutconnector(Connector* C)
{
	pOutConn = C;
}
bool Read::IsPointInside(Point P) const
{
	Point A = LeftCorner;
	Point B (LeftCorner.x + UI.ASSGN_WDTH, LeftCorner.y);
	Point C (LeftCorner.x + 1.5 * UI.ASSGN_WDTH, LeftCorner.y + UI.ASSGN_HI);
	Point D (LeftCorner.x + UI.ASSGN_WDTH/2 , LeftCorner.y + UI.ASSGN_HI);
	
	double Area2 = TriArea2(A, B, C) + TriArea2(A, C, D);
	double sum = TriArea2(A, B, P) +
		TriArea2(B, C, P) +
		TriArea2(C, D, P) +
		TriArea2(A, D, P);

	return sum == Area2;
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
	if (!IsVariable(varName)) {
		msg = "Read statement variable '" + varName + "' is not a valid variable name.";
		return false;
	}
	int idx = Findvarindex(varName, vars, varcount);
	if (idx == -1 || !vars[idx].declared) {
		msg = "Variable " + varName + " used without declaration.";
		return false;
	}
	else {
		vars[idx].initialized = true;
		return true;

	}
}

 double Read::TriArea2(Point A, Point B, Point C)
{
	return abs(
		A.x * (B.y - C.y) +
		B.x * (C.y - A.y) +
		C.x * (A.y - B.y)
	);
}
