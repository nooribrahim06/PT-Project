#pragma once
#include"Action.h"

class DebugRunAction :public Action
{
	public:

	DebugRunAction (ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};

