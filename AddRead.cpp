#include "AddRead.h"
#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"
#include <sstream>
//constructor: set the ApplicationManager pointer inside this action

AddRead::AddRead(ApplicationManager* pAppManager) : Action(pAppManager)
{
}
void AddRead::ReadActionParameters()
{
	// Get Input / Output pointers
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	//Read the (Position) parameter
	pOut->PrintMessage("Read Statement: Click to add the statement");
	while (true)
	{
		pIn->GetPointClicked(Position);
		if (pOut->IsInDrawingArea(Position))
			break;

		pOut->PrintMessage("Invalid location. Click INSIDE the drawing area.");
	}
	pOut->PrintMessage("Read Statement: Enter variable name");
	varName = pIn->GetVariable(pOut);
	pOut->ClearStatusBar();
}
void AddRead::Execute()
{
	ReadActionParameters();
	//Calculating left corner of Read statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;
	Read* pRead = new Read(Corner, varName);
	//Add the created Read statement to the list of statements in the application manager
	pManager->AddStatement(pRead);
}
