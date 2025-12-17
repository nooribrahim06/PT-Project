#include "Delete.h"
//#include "Cut.h"
#include "ApplicationManager.h"
#include "Statements/Statement.h"
#include "Connector.h"
#include "GUI/Output.h"

Delete::Delete(ApplicationManager* pApp) 
	: Action(pApp), pStat(nullptr), pConn(nullptr) {}

void Delete::ReadActionParameters()
{
	// Priority is connector if selected
	pConn = pManager->GetSelectedConn();
	pStat = nullptr;

	if (!pConn)
	{
		pStat = pManager->GetSelectedStatement();
	}
}

void Delete::Execute()
{
	Output* pOut = pManager->GetOutput();

	ReadActionParameters();
	if (!pConn && !pStat)
	{
		pOut->PrintMessage("Error: Nothing selected to delete.");
		return;
	}

	if (pConn)
	{
		// Delete the selected connector
		pManager->DeleteConnector(pConn);
		pManager->SetSelectedConn(nullptr);
		pOut->PrintMessage("Delete: Connector deleted.");
	}
	else
	{
		// Delete the selected statement and its connectors
		pManager->DeleteStatementWithConnectors(pStat);
		pOut->PrintMessage("Delete: Statement deleted.");
	}

	pManager->UpdateInterface();

}
