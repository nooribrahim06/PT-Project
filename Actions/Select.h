#pragma once
#include "..\Actions\Action.h"
#include "..\Statements\Statement.h"
class Select :
    public Action
{
	Point Click;
	Statement* pSelectedstate;
	Connector* pSelectedconn;
public:
	Select(ApplicationManager* pAppManager);
	virtual void ReadActionParameters(); // to read the position and variable name
	virtual void Execute();
};

