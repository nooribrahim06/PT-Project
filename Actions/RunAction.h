#pragma once
#include "..\Actions\Action.h"
class RunAction:public Action
{
public:
	RunAction(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();

};

