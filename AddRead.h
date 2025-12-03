#pragma once
#include "Actions/Action.h"
#include "Read.h"
class AddRead :
    public Action
{
    Point Position; // Position where the user clicks to add the stat.
	string varName;
    public:
    AddRead(ApplicationManager* pAppManager);
	virtual void ReadActionParameters(); // to read the position and variable name
	virtual void Execute(); // to create and add a Read statement
};

