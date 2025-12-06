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
Statement* Condition::Simulate(Input* pIn, Output* pOut)
{
	
	double Lhs;
	double Rhs;
	if (ValueOrVariable(LHS) == VALUE_OP) {
		Lhs = stod(LHS);
	}
	else if (ValueOrVariable(LHS) == VARIABLE_OP)
	{
		Lhs = GetVar(LHS);
	}
	if (ValueOrVariable(RHS) == VALUE_OP) {
		Rhs = stod(RHS);
	}
	else if (ValueOrVariable(RHS) == VARIABLE_OP)
	{
		Rhs = GetVar(RHS);
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
			return NULL;
		
	}
	else {
		if (pFalseOutConn)
			return pFalseOutConn->getDstStat();
	}
		return NULL;
	}


void Condition::GenerateCode(ofstream& OutFile)
{
	return;
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
	if (CompOp != "==" && CompOp != "<=" && CompOp != ">=" && CompOp != ">" && CompOp != "<"
		&& CompOp != "!=")
	{
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
	T << LHS << " " << RHS;
	Text = T.str();
}