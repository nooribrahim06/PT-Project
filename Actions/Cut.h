#pragma once
#include "Action.h"
#include "..\Statements/Statement.h"

class Cut :
    public Action
{
private:

    // Pointer to the statement we are going to cut
	Statement* pCutStat;    
    public:
    // Constructor: just passes the manager pointer to base Action
    Cut(ApplicationManager* pApp);
    // Reads any parameters needed for the action
    virtual void ReadActionParameters() override;
    virtual void Execute() override;
};

