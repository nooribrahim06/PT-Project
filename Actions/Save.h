#pragma once
#include "..\Actions\Action.h"
class Save :
    public Action
{
	string FileName;
public:
	Save(ApplicationManager* pAppManager);

	virtual void ReadActionParameters() override;

	virtual void Execute() override;
};

