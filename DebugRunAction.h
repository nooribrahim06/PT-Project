#pragma once
#include"Actions/Action.h"
class DebugRunAction :public Action
{
	public:

	DebugRunAction (ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};

