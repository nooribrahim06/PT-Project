#pragma once
#include"Actions/Action.h"
class GenerateCodeAction:public Action
{public:
	string filename_without_extension;
	GenerateCodeAction(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};

