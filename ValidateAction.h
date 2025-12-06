#pragma once
#include"Actions/Action.h"	
class ValidateAction:public Action
{
public:
	ValidateAction(ApplicationManager* pAppManager);
	void ReadActionParameters();
	virtual void Execute();
};

