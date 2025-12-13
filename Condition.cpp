#include "Condition.h"
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;
Condition::Condition(Point C, string L, string Op, string R)
{
	// to be implemented 
	int W = UI.ASSGN_WDTH;
	int H = UI.ASSGN_HI;
	Center = C;
	LHS = L;
	RHS = R;
	CompOp = Op;
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
Connector* Condition::GetTrueConn() const
{
	return pTrueOutConn;
}
void Condition::SetTrueConn(Connector* C)
{
	pTrueOutConn = C;
}
Connector* Condition::GetFalseConn() const
{
	return pFalseOutConn;
}
void Condition::SetFalseConn(Connector* C)
{
	pFalseOutConn = C;
}
void Condition::Draw(Output* pOut) const
{
	// to be implemented 
	pOut->DrawCondStatement(Center, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}
void Condition::Save(ofstream& OutFile)
{
	// to be implemented
	string Comp;
	if (CompOp == "==") Comp = "EQUL";
	else if (CompOp == "!=") Comp = "NEQL";
	else if (CompOp == ">") Comp = "GRT_";
	else if (CompOp == "<") Comp = "SML_";
	else if (CompOp == "<=") Comp = "SMLE";
	else if (CompOp == ">=") Comp = "GRTE";
	OutFile << "COND	" << GetstatementID() << "	" << Center.x << "	" << Center.y << "	" << RHS << "	" << Comp << "	" << LHS << endl;
	return;
}
void Condition::Load(ifstream& InFile)
{
	int id, x, y;
	string LHS, RHS, Comp;
	InFile >> id >> x >> y >> RHS >> Comp >> LHS;
	statementID = id;
	Center.x = x;
	Center.y = y;
	this->RHS = RHS;
	this->LHS = LHS;
	if (Comp == "EQUL") CompOp = "==";
	else if (Comp == "NEQL") CompOp = "!=";
	else if (Comp == "GRT_") CompOp = ">";
	else if (Comp == "SML_") CompOp = "<";
	else if (Comp == "SMLE") CompOp = ">=";
	else if (Comp == "GRTE") CompOp = "";
	int W = UI.ASSGN_WDTH;
	int H = UI.ASSGN_HI;
	Inlet.x = Center.x;
	Inlet.y = Center.y - H / 2;
	TrueOutlet.x = Center.x + W / 2;
	FalseOutlet.x = Center.x - W / 2;
	TrueOutlet.y = Center.y;
	FalseOutlet.y = Center.y;

	UpdateStatementText();

	return;
}
void Condition::Edit()
{
	return;
}
Statement* Condition::Simulate(Input* pIn, Output* pOut)
{

	double Lhs = 0;
	double Rhs = 0;
	if (ValueOrVariable(LHS) == VALUE_OP) {
		Lhs = stod(LHS);
	}
	else if (ValueOrVariable(LHS) == VARIABLE_OP)
	{
		Lhs = Statement::GetVar(LHS);
	}
	if (ValueOrVariable(RHS) == VALUE_OP) {
		Rhs = stod(RHS);
	}
	else if (ValueOrVariable(RHS) == VARIABLE_OP)
	{
		Rhs = Statement::GetVar(RHS);
	}
	bool compresult = false;

	if (CompOp == "==") {
		compresult = (Lhs == Rhs);
	}
	else if (CompOp == ">=") {
		compresult = (Lhs >= Rhs);
	}
	else if (CompOp == "<=") {
		compresult = (Lhs <= Rhs);
	}
	else if (CompOp == ">") {
		compresult = (Lhs > Rhs);
	}
	else if (CompOp == "<") {
		compresult = (Lhs < Rhs);
	}
	else if (CompOp == "!=") {
		compresult = (Lhs != Rhs);
	}
	if (compresult) {
		if (pTrueOutConn) {
			return pTrueOutConn->getDstStat();
		}
		else {
			pOut->PrintMessage("Runtime Error: True connector is missing");
			return NULL;
		}

	}
	else {
		if (pFalseOutConn) {
			return pFalseOutConn->getDstStat();
		}
		else {
			pOut->PrintMessage("Runtime Error: False connector is missing");
			return NULL;
		}
	}
}


void Condition::GenerateCode(ofstream& OutFile)
{
	OutFile << "if (" << Text << ")";
}
Point Condition::GetOutletPoint() const
{
	// to be implemented 
	return (-1, -1); // or FalseOutlet based on context
}
Point Condition::GetTrueOutlet() const
{
	return TrueOutlet;
}
Point Condition::GetFalseOutlet() const
{
	return FalseOutlet;
}
Point Condition::GetInletPoint() const
{
	return Inlet;
}
Connector* Condition::GetOutConnector() const
{
	//true by default
	return pTrueOutConn;
}
void Condition::SetOutconnector(Connector* C)
{
	//will not be called
}
bool Condition::IsPointInside(Point P) const
{
	bool x_inside;
	bool y_inside;
	if(P.x >= Center.x - UI.ASSGN_WDTH / 2 && P.x <= Center.x + UI.ASSGN_WDTH / 2)
		x_inside = true;
	else
		x_inside = false;
	if (P.y >= Center.y - UI.ASSGN_HI / 2 && P.y <= Center.y + UI.ASSGN_HI / 2)
		y_inside = true;
	else
		y_inside = false;
	return (x_inside && y_inside);
}
bool Condition::Isconditional() const
{
	return true;
}
bool Condition::Validate(varinfo vars[], int& varcount, string& msg)
{
	if (LHS.empty()) {
		msg = "Left hand side of condition is empty.";
		return false;
	}
	if (RHS.empty()) {
		msg = "Right hand side of condition is empty.";
		return false;
	}
	if (CompOp.empty()) {
		msg = "Operator in condition is EMPTY";
		return false;
	}
	if (CompOp != ">=" && CompOp != "==" && CompOp != "!=" && CompOp != "<=" && CompOp != ">" && CompOp != "<") {
		msg = "Operator in condition is INVALID.";
		return false;
	}

	OpType T1 = ValueOrVariable(LHS);
	if (T1 == INVALID_OP) {
		msg = "Left hand side of  condition is INVALID";
		return false;
	}
	else if (T1 == VARIABLE_OP) {

		int LHSIdx = Findvarindex(LHS, vars, varcount);
		if (LHSIdx == -1 || !vars[LHSIdx].declared) {
			msg = "Variable " + LHS + " used without declaration.";
			return false;
		}
		else if (!vars[LHSIdx].initialized) {
			msg = "Variable " + LHS + " used without initialization.";
			return false;
		}
	}
	OpType T = ValueOrVariable(RHS);
	if (T == INVALID_OP) {
		msg = "Right hand side of  condition is INVALID";
		return false;
	}
	else if (T == VARIABLE_OP) {

		int RHSIdx = Findvarindex(RHS, vars, varcount);
		if (RHSIdx == -1 || !vars[RHSIdx].declared) {
			msg = "Variable " + RHS + " used without declaration.";
			return false;
		}
		else if (!vars[RHSIdx].initialized) {
			msg = "Variable " + RHS + " used without initialization.";
			return false;
		}


	}
	return true;
}
void Condition::UpdateStatementText()
{
	// to be implemented 
	ostringstream T;
	T << LHS << " " << CompOp << " " << RHS;
	Text = T.str();
}