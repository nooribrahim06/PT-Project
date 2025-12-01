#include "VariableAssign.h"
#include "Statements/Statement.h"

using namespace std;

VariableAssign::VariableAssign(Point Lcorner, string left, string right) { 
    // Constructor implementation here
}
void VariableAssign::setLHS(const string& L) {

}
void VariableAssign::setRHS(const string& L) {

}

// Remove 'virtual' from the implementation, and add 'const' to match the header declaration
void VariableAssign::Draw(Output* pout) const {
    // Implementation here
}

void VariableAssign::Save(ofstream& OutFile)
{
}

void VariableAssign::Load(ifstream& InFile)
{
}

void VariableAssign::Simulate()
{
    // Implementation for simulating variable assignment
    // For now, this can be left empty or add a comment for TODO
}

bool VariableAssign::checkvar(varinfo vars[], int& varcount, string& msg)
{
    if (LHS.empty()) {
        msg = "Left hand side of assignment is empty.";
        return false;
    }
    if (!IsVariable(LHS)) {
        msg = "Left hand side " + LHS + " not a valid Variable";
        return false;
    }
    int LHSIdx = Findvarindex(LHS, vars, varcount);
    if (LHSIdx == -1 || !vars[LHSIdx].declared) {
                msg = "Variable " + LHS + " used without declaration.";
				return false;
    }
    if (RHS.empty()) {
        msg = "Right hand side of assignment is empty.";
        return false;
    }

        if(!IsVariable(RHS)) {
        msg = "Right hand side of assignment must be a variable.";
        return false;
	}
    int RHSIdx= Findvarindex(RHS, vars, varcount);
    if (RHSIdx == -1 || !vars[RHSIdx].declared) {
        msg = "Variable " + RHS + " used without declaration.";
        return false;
    }
    else if (!vars[RHSIdx].initialized) {
        msg = "Variable " + RHS + " used without initialization.";
        return false;
    }
    vars[LHSIdx].initialized = true;
	return true;
}
