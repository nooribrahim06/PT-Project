#include "AddOperAssign.h"
#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"
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
			break;

		pOut->PrintMessage("Invalid location. Click INSIDE the drawing area.");
	}
	
	pOut->PrintMessage("OperAssign Statement: Enter LHS variable name");
	LHS = pIn->GetVariable(pOut);
	pOut->PrintMessage("OperAssign Statement: Enter first RHS");
	RHS1 = pIn->GetString(pOut);
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
