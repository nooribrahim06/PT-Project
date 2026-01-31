#include "AddCondition.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
//constructor: set the ApplicationManager pointer inside this action

AddCondition::AddCondition(ApplicationManager* pAppManager) : Action(pAppManager)
{
}

void AddCondition::ReadActionParameters()
{
	// Get Input / Output pointers
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	//Read the (Position) parameter
	pOut->PrintMessage("Condition Statement: Click to add the statement");
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
			P3.x = Position.x;
			P3.y = Position.y + UI.ASSGN_HI / 2;
			P4.x = Position.x;
			P4.y = Position.y - UI.ASSGN_HI / 2;
			if (pManager->GetStatement(P1) == NULL && pManager->GetStatement(P2) == NULL && pManager->GetStatement(P3) == NULL && pManager->GetStatement(P4) == NULL)
				break;
		}

		pOut->PrintMessage("Invalid location. Click INSIDE the drawing area and avoid overlapping");
	}

	pOut->PrintMessage("Condition Statement: Enter Left Hand Side (LHS)");
	LHS = pIn->GetVariable(pOut);
	pOut->PrintMessage("Condition Statement: Enter Comparison Operator");
	CompOp = pIn->GetCompOperator(pOut);
	pOut->PrintMessage("Condition Statement: Enter Right Hand Side (RHS)");
	string test = pIn->GetString(pOut);
	while (true) {
		if (IsVariable(test) || IsValue(test))
			break;
		pOut->PrintMessage("Invalid input1 Enter a variable or value");
		test = pIn->GetString(pOut);
	} 
	RHS = test;
	pOut->ClearStatusBar();
}
void AddCondition::Execute()
{
	ReadActionParameters();
	//Calculating center of Condition statement block
	Condition* pCondition = new Condition(Position, LHS, CompOp, RHS);
	//Add the created Condition statement to the list of statements in the application manager
	pManager->AddStatement(pCondition);
}