#pragma once
#include "Action.h"
class Load:public Action
{
		string FileName;
	public:
		Load(ApplicationManager* pAppManager);

		virtual void ReadActionParameters() override;

		//Execute action (code depends on action type)
		virtual void Execute() override;
	};





