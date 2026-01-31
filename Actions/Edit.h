#pragma once
#include "Action.h"
#include "..\Statements\Statement.h"
#include "..\Connector.h"

// Edit action:
// Edits the *currently selected* statement.
// If no statement is selected, it just prints an error on the status bar.
class Edit :
    public Action
{
private:
    // Pointer to the statement we are going to edit
    Statement* pStat;

public:
    // Constructor: just passes the manager pointer to base Action
    Edit(ApplicationManager* pApp);

    // Reads any parameters needed for the action
    virtual void ReadActionParameters() override;

    virtual void Execute() override;
};