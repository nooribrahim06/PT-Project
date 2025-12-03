#pragma once
#include "Actions/Action.h"
#include "Condition.h"
class AddCondition :
    public Action
{
    Point Position; // Position where the user clicks to add the stat.
    string LHS;
    string CompOp;
	string RHS;
    public:
    AddCondition(ApplicationManager* pAppManager);
    virtual void ReadActionParameters(); // to read the position and condition parts
	virtual void Execute(); // to create and add a Condition statement
};

