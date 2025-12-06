#include "VariableAssign.h"
#include "Statements/Statement.h"

using namespace std;

VariableAssign::VariableAssign(Point Lcorner, string left, string right) { 
    // Constructor implementation here
	LHS = left;
    RHS = right;

    // Update the statement text
    UpdateStatementText();
    LeftCorner = Lcorner;
    pOutConn = NULL;	//No connectors yet
    Inlet.x = LeftCorner.x + UI.ASSGN_WDTH /2;
    Inlet.y = LeftCorner.y;
    Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}
void VariableAssign::setLHS(const string& L) {
	LHS = L;
	UpdateStatementText();
}
void VariableAssign::setRHS(const string& R) {
	RHS = R;
	UpdateStatementText();
}

// Remove 'virtual' from the implementation, and add 'const' to match the header declaration
void VariableAssign::Draw(Output* pOut) const {
    // Implementation here
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}

void VariableAssign::Save(ofstream& OutFile)
{
    return;
}

void VariableAssign::Edit()
{
    return;
}

Statement* VariableAssign::Simulate(Input* pIn, Output* pOut)
{
    double value = GetVar(RHS);
    SetVar(LHS, value);
    if (pOutConn != NULL)
    {
        return pOutConn->getDstStat();
    }
    else
    {
        return NULL;
    }

}

void VariableAssign::Load(ifstream& InFile)
{
    return;
}
void VariableAssign::GenerateCode(ofstream& OutFile)
{
    return;
}
void VariableAssign::UpdateStatementText()
{
    Text = LHS + " = " + RHS;
}

bool VariableAssign::Validate(varinfo vars[], int& varcount, string& msg)
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
