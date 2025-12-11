#include "OpAssign.h"
#include "Statements/Statement.h"
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;


OpAssign::OpAssign(Point Lcorner, string L, string R1, string R2, string op) {
	// Note: The LHS, RHS1, RHS2 and op should be validated inside (AddOpAssign) action
	//       before passing it to the constructor of OpAssign

	LHS = L;
	RHS1 = R1;
	RHS2 = R2;
	this->op = op;
	// Update the statement text
	UpdateStatementText();

	LeftCorner = Lcorner;
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;

	pOutConn = NULL;	//No connectors yet
}
void OpAssign::setLHS(const string& L) {
	LHS = L;
	UpdateStatementText();
}
void OpAssign::setRHS(const string& R1, const string R2, const string OP) {
	RHS1 = R1;
	RHS2 = R2;
	op = OP;
	UpdateStatementText();
}
void OpAssign::Draw(Output* pOut) const {
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}

void OpAssign::Save(ofstream& OutFile)
{
	string arthm;
	if (op == "+") arthm = "PLS";
	else if (op == "-") arthm = "MIN";
	else if (op == "*") arthm = "MUL";
	else if (op == "/") arthm = "DIV";
	OutFile << "OPAS	" << GetstatementID() << "	" << LeftCorner.x << "	" << LeftCorner.y << "	" << LHS << "	" << RHS1 << "	" << arthm << "	" << RHS2 << endl;
	return;									//OPAS	12	200	30	n	12	MUL	10
}

void OpAssign::Load(ifstream& InFile)
{
	return;
}

void OpAssign::Edit()
{
	return;
}

Statement* OpAssign::Simulate(Input* pIn, Output* pOut)
{ 
	double val1 = GetVar(RHS1);
	double val2 = GetVar(RHS2);
	double opresult = 0;
	if (ValueOrVariable(RHS1) == VALUE_OP) {
		val1 = stod(RHS1);
	}
	else if (ValueOrVariable(LHS) == VARIABLE_OP)
	{
		val1 = GetVar(RHS1);
	}
	if (ValueOrVariable(RHS2) == VALUE_OP) {
		val2 = stod(RHS2);
	}
	else if (ValueOrVariable(RHS2) == VARIABLE_OP)
	{
		val2 = GetVar(RHS2);
	}


	if (op == "+")
	{
		opresult = val1 + val2;
	}
	else if (op == "-") {
		opresult = val1 - val2;
	}
	else if (op == "*") {
		opresult = val1 * val2;
	}
	else if (op == "/") {
		if (val2 == 0) {
			pOut->PrintMessage("Runtime Error: Can't divide by 0");
			opresult = 0;
		}
		else {
			opresult = val1 / val2;
		}
	}
	SetVar(LHS, opresult);
	if (pOutConn != NULL)
	{
		return pOutConn->getDstStat();
	}
	else
	{
		return NULL;
	}
}




void OpAssign::GenerateCode(ofstream& OutFile)
{
	OutFile << LHS << " = " << RHS1 << " " << op << " " << RHS2 << ";\n";
}

Point OpAssign::GetInletPoint() const
{
	return Inlet;
}
Connector* OpAssign::GetOutConnector() const
{
	return pOutConn;
}
void OpAssign::SetOutconnector(Connector* C)
{
	pOutConn = C;
}
Point OpAssign::GetOutletPoint() const
{
	return Outlet;
}
bool OpAssign::IsPointInside(Point P) const
{
	bool x_inside = (P.x >= LeftCorner.x) && (P.x <= LeftCorner.x + UI.ASSGN_WDTH);
	bool y_inside = (P.y >= LeftCorner.y) && (P.y <= LeftCorner.y + UI.ASSGN_HI);
	return (x_inside && y_inside);
}

bool OpAssign::Validate(varinfo vars[], int& varcount, string& msg)
{
	if (LHS.empty()) {
		msg = "Left hand side of assignment is empty.";
		return false;
	}
	if (!IsVariable(LHS)) {
		msg = "Left-hand side '" + LHS + " '  is not a valid Variable name";
			return false;
	}
	if (op.empty()) {
		msg = "Operator in assignment is empty.";
		return false;
	}
	if (op != "+" && op != "-" && op != "/" && op != "*") {
		msg = "Operator in assignment is INVALID.";
		return false;
	}
	int LHSIdx = Findvarindex(LHS, vars, varcount);
	if (LHSIdx == -1 || !vars[LHSIdx].declared) {
		msg = "Variable " + LHS + " used without declaration.";
		return false;
	}
	if (!RHS1.empty()) {
		OpType T = ValueOrVariable(RHS1);
		if (T == INVALID_OP) {
			msg = "Right hand side 1 of assignment is invalid.";
			return false;
		}
		else if (T == VARIABLE_OP) {
			int RHS1Idx = Findvarindex(RHS1, vars, varcount);
			if (RHS1Idx == -1 || !vars[RHS1Idx].declared) {
				msg = "Variable " + RHS1 + " used without declaration.";
				return false;
			}
			else if (!vars[RHS1Idx].initialized) {
				msg = "Variable " + RHS1 + " used without initialization.";
				return false;
			}
		}
	}
	else {
		msg = "Right hand side 1 of assignment is empty.";
		return false;
	}

	if (!RHS2.empty()) {
		OpType T2 = ValueOrVariable(RHS2);
		if (T2 == INVALID_OP) {
			msg = "Right hand side 2 of assignment is invalid.";
			return false;
		}
		else if (T2 == VARIABLE_OP) {
			int RHS2Idx = Findvarindex(RHS2, vars, varcount);
			if (RHS2Idx == -1 || !vars[RHS2Idx].declared) {
				msg = "Variable " + RHS2 + " used without declaration.";
				return false;
			}
			else if (!vars[RHS2Idx].initialized) {
				msg = "Variable " + RHS2 + " used without initialization.";
				return false;
			}
		}
	}
	else {
		msg = "Right hand side 2 of assignment is empty.";
		return false;
	}
	
	vars[LHSIdx].initialized = true;
	return true;
}


void OpAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << " = " << RHS1 << op << RHS2;
	Text = T.str();
}