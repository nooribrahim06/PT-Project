#include "SwitchtoDesignAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Output.h"
#include "..\GUI\Input.h"
#include "..\GUI\UI_Info.h"

SwitchtoDesignAction::SwitchtoDesignAction(ApplicationManager* pAppManager):Action(pAppManager)
{
}
void SwitchtoDesignAction::ReadActionParameters() 
{
	//NO PARAMETERS//
}
void SwitchtoDesignAction::Execute() {
	Output* pOut = pManager->GetOutput();
	pOut->ClearOutputBar();
	UI.AppMode = DESIGN;
	pOut->CreateDesignToolBar();
	pOut->ClearStatusBar();
	pOut->PrintMessage("Switched To Design Mode");
	pManager->UpdateInterface();



}

