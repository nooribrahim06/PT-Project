#ifndef ADD_END_H
#define ADD_END_H
#include "Action.h"
#include "..\Statements\End.h"
class AddEnd :
    public Action
{
	Point Position; // Position where the user clicks to add the stat.
public:
	AddEnd(ApplicationManager* pAppManager);
	virtual void ReadActionParameters(); // to only read the position
	virtual void Execute(); // to create and add an End statement
};

#endif