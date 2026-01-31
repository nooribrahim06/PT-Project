#pragma once
#include "Action.h"
#include "..\Statements\Write.h"

class AddWrite :
    public Action
{
    Point Position; // Position where the user clicks to add the stat.
    string varName;
    public:
    AddWrite(ApplicationManager* pAppManager);
    virtual void ReadActionParameters(); // to read the position and variable name
	virtual void Execute(); // to create and add a Write statement
};

