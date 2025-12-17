#include "AddVarAssign.h"
#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"
#include <sstream>

AddVarAssign::AddVarAssign(ApplicationManager* pAppManager) : Action(pAppManager)
{
}
void AddVarAssign::ReadActionParameters()
{
	// Get Input / Output pointers
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Variable Assignment Statement: Click to add the statement");
	while (true)
	{
		pIn->GetPointClicked(Position);
		if (pOut->IsInDrawingArea(Position))
			break;

		pOut->PrintMessage("Invalid location. Click INSIDE the drawing area.");
	}

	pOut->ClearStatusBar();

	// get LHS
	pOut->PrintMessage("Variable Assignment Statement: Add the variable to be assigned");
	LHS = pIn->GetVariable(pOut);
	pOut->ClearStatusBar();
	// get RHS
	pOut->PrintMessage("Variable Assignment Statement: Add the variable to assign from");
	RHS = pIn->GetVariable(pOut);
	pOut->ClearStatusBar();
}
void AddVarAssign::Execute()
{
	ReadActionParameters();
	// creating the object
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;

	VariableAssign* pVarAssign = new VariableAssign(Corner, "", "");
	// setting LHS and RHS
	pVarAssign->setLHS(LHS);
	pVarAssign->setRHS(RHS);
	// adding to the statement list
	pManager->AddStatement(pVarAssign);
}