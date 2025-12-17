#include "AddStart.h"
#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"
#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddStart::AddStart(ApplicationManager* pAppManager) : Action(pAppManager)
{
}
void AddStart::ReadActionParameters()
{
	// Get Input / Output pointers
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	//Read the (Position) parameter

	pOut->PrintMessage("Start Statement: Click to add the statement");
	while (true)
	{
		pIn->GetPointClicked(Position);
		if (pOut->IsInDrawingArea(Position))
			break;

		pOut->PrintMessage("Invalid location. Click INSIDE the drawing area.");
	}
	pOut->ClearStatusBar();
}
void AddStart::Execute()
{
	ReadActionParameters();
	//Calculating left corner of Start statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;
	Start* pStart = new Start(Corner);
	//Add the created Start statement to the list of statements in the application manager
	pManager->AddStatement(pStart);
}