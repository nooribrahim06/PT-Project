#pragma once
#include "Action.h"
#include "..\Statements\Statement.h"

class Paste :
    public Action
{
public:
    Paste(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
private:
    Statement* pCopiedStat;
};

