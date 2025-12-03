#pragma once
#include "Actions/Action.h"
#include "Statements/Statement.h"
#include "OpAssign.h"
class AddOperAssign :
    public Action
{
    Point Position; // Position where the user clicks to add the stat.
    string LHS;
    string Op;
	string RHS1;
	string RHS2;
    public:
    AddOperAssign(ApplicationManager* pAppManager);
    virtual void ReadActionParameters(); // to only read the position
	virtual void Execute(); // to create and add a Start statement
};

