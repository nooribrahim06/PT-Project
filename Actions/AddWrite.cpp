#include "AddWrite.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include <sstream>

AddWrite::AddWrite(ApplicationManager* pAppManager) : Action(pAppManager)
{
}
void AddWrite::ReadActionParameters()
{
	// Get Input / Output pointers
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	//Read the (Position) parameter
	pOut->PrintMessage("Write Statement: Click to add the statement");
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

	do {
		pOut->PrintMessage("Write Statement: Enter variable name, value, or a message");
		varName = pIn->GetString(pOut);

		if (varName.empty())
			continue;

		bool isQuoted = (varName.front() == '"' && varName.back() == '"');
		bool isValue = IsValue(varName);
		bool isVariable = IsVariable(varName);

		if (isQuoted || isValue || isVariable)
			break;

	} while (true);
	pOut->ClearStatusBar();
}
void AddWrite::Execute()
{
	ReadActionParameters();
	//Calculating left corner of Write statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;
	Write* pWrite = new Write(Corner, varName);
	//Add the created Write statement to the list of statements in the application manager
	pManager->AddStatement(pWrite);
}