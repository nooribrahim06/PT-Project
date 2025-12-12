#pragma once
#include "Actions/Action.h"
#include "Statements/Statement.h"
class Copy :
    public Action
{
private:
    Statement* pCopiedStat; // Pointer to the copied statement
public:
    Copy(ApplicationManager* pApp);
    virtual void ReadActionParameters() override;
    virtual void Execute() override;
};

