#include "AddOperAssign.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include <sstream>
using namespace std;


AddOperAssign::AddOperAssign(ApplicationManager* pAppManager) : Action(pAppManager)
{
}
void AddOperAssign::ReadActionParameters()
{
	// Get Input / Output pointers
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	//Read the (Position) parameter
	pOut->PrintMessage("OperAssign Statement: Click to add the statement");
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

	
	pOut->PrintMessage("OperAssign Statement: Enter LHS variable name");
	LHS = pIn->GetVariable(pOut);
	pOut->PrintMessage("OperAssign Statement: Enter first RHS");
	/*RHS1 = pIn->GetString(pOut);*/
	string test = pIn->GetString(pOut);
	while (true) {
		if (IsVariable(test) || IsValue(test))
			break;
		pOut->PrintMessage("Invalid input1 Enter a variable or value");
		test = pIn->GetString(pOut);
	}
	RHS1 = test;
	pOut->PrintMessage("OperAssign Statement: Enter arithmetic operator (+, -, *, /)");
	Op = pIn->GetArithOperator(pOut);
	pOut->PrintMessage("OperAssign Statement: Enter second RHS");
	test = pIn->GetString(pOut);
	while (true) {
		if (IsVariable(test) || IsValue(test))
			break;
		pOut->PrintMessage("Invalid input2 Enter a variable or value");
		test = pIn->GetString(pOut);
	}
	RHS2 = test;
	pOut->ClearStatusBar();
}
void AddOperAssign::Execute()
{
	ReadActionParameters();
	//Calculating left corner of OperAssign statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;
	OpAssign* pOpAssign = new OpAssign(Corner, LHS, RHS1, RHS2, Op);
	//Add the created OperAssign statement to the list of statements in the application manager
	pManager->AddStatement(pOpAssign);
}
