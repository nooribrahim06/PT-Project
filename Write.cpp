#include "Write.h"
#include <iostream>
#include <fstream>
using namespace std;
int Write::OutputCount = 0;
void Write::ResetOutputCount()
{
	OutputCount = 0;
}
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
	OutFile << "WRTE	" << GetstatementID() << "	" << LeftCorner.x << "	" << LeftCorner.y << "	" << var << endl;
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
Statement* Write::Simulate(Input* pIn, Output* pOut)
{
	
	double value = 0;
	OpType t = ValueOrVariable(var);
	if (t == VALUE_OP) {
		value = stod(var);
	}
	else if (t==VARIABLE_OP){
		value=  Statement::GetVar(var);
	}
	string msg = var + " = " + to_string(value);
		pOut->PrintOnOutputBar(msg,OutputCount);
		OutputCount++;
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



void Write::GenerateCode(ofstream& OutFile)
{
	OutFile << "cout << " << var << " ;\n";
}

Point Write::GetOutletPoint() const
{
	return Outlet;
}
Point Write::GetInletPoint() const
{
	return Inlet;
}

Connector* Write::GetOutConnector() const
{
	return pOutConn;
}

void Write::SetOutconnector(Connector* C)
{
	pOutConn = C;
}

bool Write::IsPointInside(Point P) const
{
	Point A = LeftCorner;
	Point B(LeftCorner.x + UI.ASSGN_WDTH, LeftCorner.y);
	Point C(LeftCorner.x +  UI.ASSGN_WDTH /2, LeftCorner.y + UI.ASSGN_HI);
	Point D(LeftCorner.x - UI.ASSGN_WDTH / 2, LeftCorner.y + UI.ASSGN_HI);

	double Area2 = TriArea2(A, B, C) + TriArea2(A, C, D);
	double sum = TriArea2(A, B, P) +
		TriArea2(B, C, P) +
		TriArea2(C, D, P) +
		TriArea2(A, D, P);

	return sum == Area2;
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

double Write::TriArea2(Point A, Point B, Point C)
{
	return abs(
		A.x * (B.y - C.y) +
		B.x * (C.y - A.y) +
		C.x * (A.y - B.y)
	);
}
