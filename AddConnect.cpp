#include "AddConnect.h"
#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"
#include <sstream>
AddConnect::AddConnect(ApplicationManager* pAppManager) : Action(pAppManager)
{
}
// this is need a lot of validations
void AddConnect::ReadActionParameters()
{
	// Get Input / Output pointers
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	//Read the (Source and Destination Statements) parameters
	pOut->PrintMessage("Connector: Click on the source statement");
	Point P1;
	pIn->GetPointClicked(P1);
	SrcStat = pManager->GetStatement(P1);
	while (SrcStat == NULL || SrcStat->IsEnd()) // keep asking until a valid statement is selected
	{
		pOut->PrintMessage("Connector: Invalid selection. Please click on a valid source statement");
		pIn->GetPointClicked(P1);
		SrcStat = pManager->GetStatement(P1);
	}

	// if it is conditional , we need to check no or yes connector
	//if (SrcStat->Isconditional())
	//{
	//	pOut->PrintMessage("Connector: Is this a 'Yes' or 'No' branch? Click 'Y' for Yes and 'N' for No");
	//	string branch;
	//	while (true)
	//	{
	//		branch = pIn->GetString(pOut);
	//		if (branch == "Y" || branch == "y")
	//		{
	//			// check if yes connector already exists
	//			if()
	//		}
	//		else if (branch == "N" || branch == "n")
	//		{
	//			// check if no connector already exists
	//			bool noExists = false;
	//			for (int i = 0; i < pManager->ConnCount; i++)
	//			{
	//				if (pManager->ConnList[i]->getSrcStat() == SrcStat)
	//				{
	//					noExists = true;
	//					break;
	//				}
	//			}
	//			if (noExists)
	//			{
	//				pOut->PrintMessage("Connector: 'No' branch already exists. Please choose 'Yes' branch.");
	//			}
	//			else
	//			{
	//				break; // valid no branch
	//			}
	//		}
	//		else
	//		{
	//			pOut->PrintMessage("Connector: Invalid input. Please click 'Y' for Yes and 'N' for No");
	//		}
	//	}
	//}


	pOut->PrintMessage("Connector: Click on the destination statement");
	Point P2;
	pIn->GetPointClicked(P2);
	DstStat = pManager->GetStatement(P2);
	while (DstStat == NULL || DstStat == SrcStat || DstStat->IsStart()) // keep asking until a valid statement is selected
	{
		pOut->PrintMessage("Connector: Invalid selection. Please click on a valid destination statement");
		pIn->GetPointClicked(P2);
		DstStat = pManager->GetStatement(P2);
	}
	pOut->ClearStatusBar();
}
void AddConnect::Execute()
{
	ReadActionParameters();
	SrcPoint = SrcStat->GetOutletPoint();
	DstPoint = DstStat->GetInletPoint();
	//Calculating source and destination points
	// For simplicity, we assume connectors start from the bottom center of the source statement
	// and end at the top center of the destination statement.
	Connector* pConn = new Connector(SrcStat, DstStat);
	pConn->setStartPoint(SrcPoint);
	pConn->setEndPoint(DstPoint);
	//Add the created Connector to the list of connectors in the application manager
	pManager->AddConnector(pConn);
}