#include "AddDeclare.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
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
	while (true)
	{
		pIn->GetPointClicked(Position);
		if (pOut->IsInDrawingArea(Position))
		{
			Point P1, P2, P3,P4;
			P1.x = Position.x - UI.ASSGN_WDTH/2;
			P1.y = Position.y;
			P2.x = Position.x + UI.ASSGN_WDTH/2;
			P2.y = Position.y;
			P3.x = Position.x + UI.ASSGN_WDTH/2;
			P3.y = Position.y + UI.ASSGN_HI;
			P4.x = Position.x - UI.ASSGN_WDTH / 2;
			P4.y = Position.y + UI.ASSGN_HI;
			if (pManager->GetStatement(P1) == NULL && pManager->GetStatement(P2) == NULL && pManager->GetStatement(P3) == NULL && pManager->GetStatement(P4) == NULL)
				break;
		}

		pOut->PrintMessage("Invalid location. Click INSIDE the drawing area and avoid overlapping");
	}

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
