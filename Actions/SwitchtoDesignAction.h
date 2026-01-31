#pragma once
#include "Action.h"

class SwitchtoDesignAction :public Action
{
public:
	SwitchtoDesignAction(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};

