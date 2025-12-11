#include "Select.h"
#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"
#include <sstream>

Select::Select(ApplicationManager* pAppManager) : Action(pAppManager)
{
	pSelectedconn = NULL;
	pSelectedstate = NULL;
}
void Select::ReadActionParameters()
{
	// Get Input / Output pointers
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	pSelectedconn = NULL;
	pSelectedstate = NULL;

	pOut->PrintMessage("Select: Click on a Statement or Connector");
	pIn->GetPointClicked(Click);

	// keep asking WHILE there is NO statement AND NO connector
	Statement* pStat = pManager->GetStatement(Click);
	Connector* pConn = pManager->GetConnector(Click);
	int count = 0;
	while (count < 5 && !pStat && !pConn)
	{
		pOut->PrintMessage("Invalid selection, click on a Statement or Connector");
		pIn->GetPointClicked(Click);

		pStat = pManager->GetStatement(Click);
		pConn = pManager->GetConnector(Click);
		count++;
	}

	// if both exist in same area, choose priority (e.g. statement first)
	if (pStat)
		pSelectedstate = pStat;
	if (pConn && !pStat)       // only pick connector if no statement
		pSelectedconn = pConn;

	pOut->ClearStatusBar();
}

void Select::Execute() {
	ReadActionParameters();
	if (pSelectedconn)
	{
		if (pSelectedconn->IsSelected())
		{
			pSelectedconn->Setselected(false);
			pManager->SetSelectedConn(NULL);
		}
		else
		{
			pSelectedconn->Setselected(true);
			if (pManager->GetSelectedConn())
				(pManager->GetSelectedConn())->Setselected(false);
			if (pManager->GetSelectedStatement())
				(pManager->GetSelectedStatement())->SetSelected(false);
			pManager->SetSelectedConn(pSelectedconn);
		}
	}
	if (pSelectedstate)
	{
		if (pSelectedstate->IsSelected())
		{
			pSelectedstate->SetSelected(false);
			pManager->SetSelectedStatement(NULL);
		}
		else
		{
			pSelectedstate->SetSelected(true);
			if(pManager->GetSelectedStatement())
				(pManager->GetSelectedStatement())->SetSelected(false);
			if (pManager->GetSelectedConn())
				(pManager->GetSelectedConn())->Setselected(false);
			pManager->SetSelectedStatement(pSelectedstate);
		}
	}
}