#include "RunAction.h"
#include"GUI/Output.h"
#include"ApplicationManager.h"
#include"Write.h"
RunAction::RunAction(ApplicationManager* pAppManager):Action(pAppManager)
{
}
void RunAction::ReadActionParameters() {
	// No parameters to read for run action
}
void RunAction::Execute() {

	string Runmsg;
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->ClearOutputBar();
	bool Run = pManager->Run(Runmsg);

	Write::ResetOutputCount();
	if (!Run) {
		pOut->PrintMessage(Runmsg);
	}
	else {
		pOut->PrintMessage("Run Successfully. ");
	}
	
	
	

}