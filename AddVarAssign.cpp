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
		{
			Point P1, P2, P3, P4;
			P1.x = Position.x - UI.ASSGN_WDTH / 2;
			P1.y = Position.y;
			P2.x = Position.x + UI.ASSGN_WDTH / 2;
			P2.y = Position.y;
			P3.x = Position.x + UI.ASSGN_WDTH / 2;
			P3.y = Position.y + UI.ASSGN_HI;
			P4.x = Position.x - UI.ASSGN_WDTH / 2;
			P4.y = Position.y + UI.ASSGN_HI;
			if (pManager->GetStatement(P1) == NULL && pManager->GetStatement(P2) == NULL && pManager->GetStatement(P3) == NULL && pManager->GetStatement(P4) == NULL)
				break;
		}

		pOut->PrintMessage("Invalid location. Click INSIDE the drawing area and avoid overlapping");
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