#include "AddConnect.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include <sstream>
AddConnect::AddConnect(ApplicationManager* pAppManager) : Action(pAppManager)
{
	conditionbranch = true;
}
// this is need a lot of validations
void AddConnect::ReadActionParameters()
{
	// Get Input / Output pointers
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	//Read the (Source and Destination Statements) parameters
	Point P1;
	pOut->PrintMessage("Connector: Click on the source statement");

	while (true)
	{
		//pOut->PrintMessage("Connector: Click on the source statement");
		pIn->GetPointClicked(P1);
		SrcStat = pManager->GetStatement(P1);

		if (!SrcStat || SrcStat->IsEnd()) {
			pOut->PrintMessage("Invalid selection. Please click on a valid *non-End* source statement");
			continue;
		}
		if (!IsvalidSrc(SrcStat, pIn, pOut)) {
			pOut->PrintMessage("Invalid source for connector (already has connector on that branch)");
			continue;
		}
		break; // valid source
	}


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
	// case conditional 
	if (SrcStat->Isconditional()) {
		Condition* pCond = dynamic_cast <Condition*>(SrcStat);
		if (conditionbranch)
		{
			SrcPoint = pCond->GetTrueOutlet();
		}
		else
			SrcPoint = pCond->GetFalseOutlet();
	}
	else {
		SrcPoint = SrcStat->GetOutletPoint();
	}
	DstPoint = DstStat->GetInletPoint();
	//Calculating source and destination points
	// For simplicity, we assume connectors start from the bottom center of the source statement
	// and end at the top center of the destination statement.
	Connector* pConn = new Connector(SrcStat, DstStat);
	pConn->setStartPoint(SrcPoint);
	pConn->setEndPoint(DstPoint);
	if (SrcStat->Isconditional()) {
		Condition* pCond = dynamic_cast <Condition*>(SrcStat);
		if (conditionbranch)
			pCond->SetTrueConn(pConn);
		else
			pCond->SetFalseConn(pConn);
	}
	else
	{
		SrcStat->SetOutconnector(pConn);
	}

	//Add the created Connector to the list of connectors in the application manager
	pManager->AddConnector(pConn);
}

bool AddConnect::IsvalidSrc(Statement* stat,Input* pIn, Output* pOut)
{
	if (!stat) return false;

	// case1: condition statement
	if (stat->Isconditional()) {
		pOut->PrintMessage("conditional, please type Y or N branch");
		string branch = pIn->GetString(pOut);

		while (branch != "Y" && branch != "y" && branch != "N" && branch != "n") {
			pOut->PrintMessage("Invalid! Enter Y or N");
			branch = pIn->GetString(pOut);
		}

		Condition* pCond = dynamic_cast<Condition*>(stat);
		if (!pCond) return false;   // safety

		if (branch == "Y" || branch == "y") {
			if (pCond->GetTrueConn()) {
				return false;       // already has true branch
			}
			conditionbranch = true;
			return true;
		}
		else {
			if (pCond->GetFalseConn()) {
				return false;       // already has false branch
			}
			conditionbranch = false;
			return true;
		}
	}
	// case 2: normal statement 
	else {
		if (stat->GetOutConnector())
			return false;           // already has outgoing connector
		return true;
	}
}
