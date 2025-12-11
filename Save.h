#pragma once
#include "Actions/Action.h"
class Save :
    public Action
{
	string FileName;
public:
	Save(ApplicationManager* pAppManager);

	virtual void ReadActionParameters() override;

	//Execute action (code depends on action type)
	virtual void Execute() override;
};

