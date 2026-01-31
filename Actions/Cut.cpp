#include "Cut.h"
#include "..\ApplicationManager.h"
#include "..\Statements\Statement.h"
#include "..\Connector.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

Cut::Cut(ApplicationManager* pApp) 
	: Action(pApp), pCutStat(nullptr) {}

void Cut::ReadActionParameters()
{
	pCutStat = nullptr;
	Output* pOut = pManager->GetOutput();

	if (pManager->GetSelectedConn())
	{
		pOut->PrintMessage("Error: Cut works on statements only. Select a statement.");
		return;
	}

	pCutStat = pManager->GetSelectedStatement();
	if (!pCutStat)
	{
		pOut->PrintMessage("Error: No statement selected to cut.");
		return;
	}
}

void Cut::Execute()
{
	ReadActionParameters();

	if (!pCutStat) return;

	Output* pOut = pManager->GetOutput();
	// Clear clipboard first
	pManager->ClearClipboard();
	//Put a Clone of the selected statement in the clipboard
	Statement* clip = pCutStat->Clone();
	clip->SetSelected(false);  // prevent “clipboard copy looks selected” bugs
	clip->SetOutconnector(nullptr);
	pManager->SetClipboard(clip);
	// Set clipboard to the Cloned cut statement
	pCutStat->SetSelected(false); //avoid highlighting issues
    pManager->DeleteStatementWithConnectors(pCutStat); //delete the original statement
	
	pOut->PrintMessage("Cut: Statement cut to clipboard.");
	pManager->UpdateInterface();
}
