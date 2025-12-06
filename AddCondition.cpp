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