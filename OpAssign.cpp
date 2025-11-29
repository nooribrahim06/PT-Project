#include "OpAssign.h"
#include "Statements/Statement.h"
#include <sstream>

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
}

void OpAssign::Load(ifstream& InFile)
{
}

void OpAssign::Simulate()
{
}
void OpAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << " = " << RHS1 << op << RHS2;
	Text = T.str();
}
