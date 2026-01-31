#pragma once
#include"Action.h"
class GenerateCodeAction:public Action
{	
	string FileName;
public:	
	GenerateCodeAction(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};

