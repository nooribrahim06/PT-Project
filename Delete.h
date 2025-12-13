#pragma once
#include "Actions/Action.h"
#include "Statements/Statement.h"
#include "Connector.h"

class Delete :
    public Action
{
    private:
    // Pointer to the statement we are going to delete
    Statement* pStat; 
    Connector* pConn;

    public:
    // Constructor: just passes the manager pointer to base Action
    Delete(ApplicationManager* pApp);
    // Reads any parameters needed for the action
    virtual void ReadActionParameters() override;
    virtual void Execute() override;
    // doing Undo/Redo bonus later, add them here
    // virtual void Undo() override;
	// virtual void Redo() override;
};

