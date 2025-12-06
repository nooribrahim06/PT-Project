#include "ValidateAction.h"
#include "ApplicationManager.h"
#include"GUI/Output.h"

ValidateAction::ValidateAction(ApplicationManager* pAppManager) :Action(pAppManager)
{
}
 
void ValidateAction::ReadActionParameters()
 {
	 // No parameters to read for validate action
}

 void ValidateAction::Execute()
 {
	
	 string valimsg;
	bool valid= pManager->ValidateAll(valimsg);
	Output* pOut = pManager->GetOutput();
	if (valid) {
		pOut->PrintMessage("No Errors " + valimsg);
	}
	else {
		pOut->PrintMessage("Error:" + valimsg);
	}