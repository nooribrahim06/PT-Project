#pragma once
#include "Actions\Action.h"
#include "VariableAssign.h"
class AddVarAssign :
    public Action
{
    Point Position; // Position where the user clicks to add the stat.
    string LHS;
	string RHS;
    public:
    AddVarAssign(ApplicationManager* pAppManager);
	virtual void ReadActionParameters(); // to only read the position and LHS, RHS
	virtual void Execute(); // to create and add a Variable Assign statement
};

