#pragma once
#include "Actions/Action.h"
#include "Declare.h"
class AddDeclare :
    public Action
{
    Point Position; // Position where the user clicks to add the stat.
	string varName;
    public:
    AddDeclare(ApplicationManager* pAppManager);
    virtual void ReadActionParameters(); // to only read the position and variable name
	virtual void Execute(); // to create and add a Declare statement
};

