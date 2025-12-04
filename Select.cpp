#include "Select.h"
#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"
#include <sstream>

Select::Select(ApplicationManager* pAppManager) : Action(pAppManager)
{
}
void Select::ReadActionParameters() {
	// Get Input / Output pointers
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	//Read the (Position) parameter
	pOut->PrintMessage("Write Statement: Click to add the statement");
	pIn->GetPointClicked(Click);
	while (!pManager->GetStatement(Click) || !pManager->GetConnector(Click))
	{
		pOut->PrintMessage("Invalid Selectio , Try Again");
		pIn->GetPointClicked(Click);
	}
}
void Select::Execute() {
	ReadActionParameters();
	// to be implemented 
}