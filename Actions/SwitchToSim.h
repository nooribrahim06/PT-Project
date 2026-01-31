#pragma once
#include "Action.h"
class SwitchToSim :
    public Action
{
public:
    SwitchToSim(ApplicationManager* pManager);
    virtual void ReadActionParameters();
    void Execute();
};

