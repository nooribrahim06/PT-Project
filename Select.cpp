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
//void Select::ReadActionParameters() {
//	// Get Input / Output pointers
//	Input* pIn = pManager->GetInput();
//	Output* pOut = pManager->GetOutput();
//	//Read the (Position) parameter
//	pOut->PrintMessage("Select Statement: Click to a Statement or Connector");
//	pIn->GetPointClicked(Click);
//	while (!pManager->GetStatement(Click) || !pManager->GetConnector(Click))
//	{
//		pOut->PrintMessage("Invalid Selection , Try Again");
//		pIn->GetPointClicked(Click);
//	}
//	if (pManager->GetStatement(Click))
//		pSelectedstate = pManager->GetStatement(Click);
//	if (pManager->GetConnector(Click))
//		pSelectedconn = pManager->GetConnector(Click);
//}
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

void Select::Execute()
{
    // This sets pSelectedstate OR pSelectedconn (or both NULL) based on click
    ReadActionParameters();

    // What was selected BEFORE this click
    Statement* oldStat = pManager->GetSelectedStatement();
    Connector* oldConn = pManager->GetSelectedConn();

    // =========== CASE 1: user clicked a connector ===========
    if (pSelectedconn)
    {
        // Clicked the SAME connector -> toggle OFF
        if (pSelectedconn == oldConn)
        {
            pSelectedconn->Setselected(false);
            pManager->SetSelectedConn(nullptr);
        }
        else
        {
            // Unselect previously selected stuff
            if (oldStat)
            {
                oldStat->SetSelected(false);
                pManager->SetSelectedStatement(nullptr);
            }
            if (oldConn)
                oldConn->Setselected(false);

            // Select this connector
            pSelectedconn->Setselected(true);
			if (pManager->GetSelectedConn())
				(pManager->GetSelectedConn())->Setselected(false);
            pManager->SetSelectedConn(pSelectedconn);
        }
    }
    // =========== CASE 2: user clicked a statement ===========
    else if (pSelectedstate)
    {
        // Clicked the SAME statement -> toggle OFF
        if (pSelectedstate == oldStat)
        {
            pSelectedstate->SetSelected(false);
            pManager->SetSelectedStatement(nullptr);
        }
        else
        {
            // Unselect previously selected stuff
            if (oldConn)
            {
                oldConn->Setselected(false);
                pManager->SetSelectedConn(nullptr);
            }
            if (oldStat)
                oldStat->SetSelected(false);

            // Select this statement
            pSelectedstate->SetSelected(true);
			if(pManager->GetSelectedStatement())
				(pManager->GetSelectedStatement())->SetSelected(false);
            pManager->SetSelectedStatement(pSelectedstate);
        }
    }
    // =========== CASE 3: clicked empty area ===========
    // both pSelectedconn and pSelectedstate are null -> do nothing

    pManager->UpdateInterface();
}

