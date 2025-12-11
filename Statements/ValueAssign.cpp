#include "ValueAssign.h"
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

ValueAssign::ValueAssign(Point Lcorner, string LeftHS, double RightHS)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of ValueAssign
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();

	LeftCorner = Lcorner;
	
	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH /2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;	
}

void ValueAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void ValueAssign::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
}


void ValueAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
	
}

void ValueAssign::Save(ofstream& OutFile)
{
	return;
}

void ValueAssign::Edit()
{
	// to be implemented
	return;
}

Statement* ValueAssign::Simulate(Input* pIn, Output* pOut)
{
	Statement::SetVar(LHS, RHS);

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

void ValueAssign::Load(ifstream& InFile)
{
	return;
}


void ValueAssign::GenerateCode(ofstream& OutFile)
{
	OutFile << LHS << " = " << RHS << " ;\n";
}


bool ValueAssign::Validate(varinfo vars[], int& varcount, string& msg)
{
	if (LHS.empty()) {
		msg = "Left hand side of assignment is empty.";
		return false;
	}
	if (!IsVariable(LHS)) {
		msg = "Left hand side ' " + LHS + " ' not a valid Variable";
		return false;
	}
	int LHSIdx = Findvarindex(LHS, vars, varcount);
	if (LHSIdx == -1 || !vars[LHSIdx].declared) {
		msg = "Variable ' " + LHS + " ' used without declaration.";
		return false;
	}
	if (to_string(RHS).empty()) {
		msg = "Right hand side of assignment is empty.";
		return false;
	}
	if (!IsValue(to_string(RHS))) {
		msg = "Right hand side of assignment '" + to_string(RHS) + "' is not a valid value.";
		return false;
	}

	vars[LHSIdx].initialized = true;
	return true;

}
Point ValueAssign::GetOutletPoint() const
{
	return Outlet;
}
Point ValueAssign::GetInletPoint() const
{
	return Inlet;
}

Connector* ValueAssign::GetOutConnector() const
{
	return pOutConn;
}

void ValueAssign::SetOutconnector(Connector* C)
{
	pOutConn = C;
}

bool ValueAssign::IsPointInside(Point P) const
{
	if (P.x >= LeftCorner.x && P.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.ASSGN_HI)
		return true;
	else
		return false;
}





//This function should be called when LHS or RHS changes
void ValueAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T<<LHS<<" = "<<RHS;	
	Text = T.str();	 
}