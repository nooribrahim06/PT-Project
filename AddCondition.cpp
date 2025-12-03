#include "AddCondition.h"
#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"
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
	pIn->GetPointClicked(Position);
	pOut->PrintMessage("Condition Statement: Enter Left Hand Side (LHS)");
	LHS = pIn->GetVariable(pOut);
	pOut->PrintMessage("Condition Statement: Enter Comparison Operator");
	CompOp = pIn->GetCompOperator(pOut);
	pOut->PrintMessage("Condition Statement: Enter Right Hand Side (RHS)");
	RHS = pIn->GetVariable(pOut);
	pOut->ClearStatusBar();
}
void AddCondition::Execute()
{
	ReadActionParameters();
	//Calculating center of Condition statement block
	string FullRHS = CompOp + " " + RHS;
	Condition* pCondition = new Condition(Position, LHS, FullRHS);
	//Add the created Condition statement to the list of statements in the application manager
	pManager->AddStatement(pCondition);
}