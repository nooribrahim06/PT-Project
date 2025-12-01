#include "OpAssign.h"
#include "Statements/Statement.h"

using namespace std;

OpAssign::OpAssign(Point Lcorner, string L, string R1, string R2, string op) {

}
void OpAssign::setLHS(const string& L) {

}
void OpAssign::setRHS(const string& R1, const string R2, const string OP) {

}
void OpAssign::Draw(Output* pOut) const {

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

void OpAssign::GenerateCode(ofstream& OutFile)
{
	// to be implemented
}

bool OpAssign::checkvar(varinfo vars[], int& varcount, string& msg)
{
	if (LHS.empty()) {
		msg = "Left hand side of assignment is empty.";
		return false;
	}
	if (!IsVariable(LHS)) {
		msg = "Left-hand side '" + LHS + " '  is not a valid Variable name";
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





	

