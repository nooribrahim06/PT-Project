#include "RunAction.h"
#include"GUI/Output.h"
#include"ApplicationManager.h"
RunAction::RunAction(ApplicationManager* pAppManager):Action(pAppManager)
{
}
void RunAction::ReadActionParameters() {
	// No parameters to read for run action
}
void RunAction::Execute() {
	
	string Runmsg;
	bool Run = pManager->Run(Runmsg);
	Output* pOut = pManager->GetOutput();
	if (Run) {
		pOut->PrintMessage(Runmsg);
	}
	else {
		pOut->PrintMessage( Runmsg);
	}
	

}