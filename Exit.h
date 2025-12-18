#pragma once
#include "Actions/Action.h"
class Exit :
    public Action
{
    public:
    Exit(ApplicationManager* pAppManager);
    virtual void ReadActionParameters(); // No parameters to read
	virtual void Execute(); // to exit the application
};

