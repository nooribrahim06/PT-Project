#pragma once
#include "Action.h"
#include "..\Statements\Statement.h"
#include "..\Statements\condition.h"
class AddConnect :
    public Action
{
	Statement* SrcStat; // Source Statement
	Statement* DstStat; // Destination Statement
	Point SrcPoint;  // Source Point
	Point DstPoint;  // Destination Point
	bool conditionbranch;
	public:
		AddConnect(ApplicationManager* pAppManager);
		virtual void ReadActionParameters(); // to read source and destination statements
		virtual void Execute(); // to create and add a Connector
		bool IsvalidSrc(Statement* stat,Input* pIn, Output* pOut);
};

