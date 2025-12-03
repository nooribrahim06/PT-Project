#include "AddDeclare.h"
#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"
#include <sstream>
using namespace std;

AddDeclare::AddDeclare(ApplicationManager* pAppManager) : Action(pAppManager)
{
}
void AddDeclare::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	
	//Read the (Position) parameter
	pOut->PrintMessage("Declare Statement: Click to add the statement");
	pIn->GetPointClicked(Position);

	// Read the variable name
	pOut->PrintMessage("Declare Statement: Enter the variable name");
	varName = pIn->GetVariable(pOut);

	// variable name will be validated later in Declare::checkvar during validation phase

	pOut->ClearStatusBar();
}

void AddDeclare::Execute()
{
		ReadActionParameters();
	//Calculating left corner of Declare statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;
	Declare* pDeclare = new Declare(Corner, varName);
	//Add the created Declare statement to the list of statements in the application manager
	pManager->AddStatement(pDeclare);
}
