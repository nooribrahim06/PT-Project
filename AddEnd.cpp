#include "AddEnd.h"
#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"
#include <sstream>
using namespace std;


//constructor: set the ApplicationManager pointer inside this action
AddEnd::AddEnd(ApplicationManager* pAppManager) : Action(pAppManager)
{
}
void AddEnd::ReadActionParameters()
{
	// Get Input / Output pointers
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	//Read the (Position) parameter
	pOut->PrintMessage("End Statement: Click to add the statement");
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
}

void AddEnd::Execute()
{
	ReadActionParameters();
	//Calculating left corner of End statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;
	End* pEnd = new End(Corner);
	//Add the created End statement to the list of statements in the application manager
	pManager->AddStatement(pEnd);
}