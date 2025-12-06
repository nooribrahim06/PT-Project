#include "GenerateCodeAction.h"
#include "ApplicationManager.h"
#include "GUI/Output.h"
#include "GUI/Input.h"
#include "GUI/UI_Info.h"

GenerateCodeAction::GenerateCodeAction(ApplicationManager* pAppManager):Action(pAppManager)
{
}
void GenerateCodeAction::ReadActionParameters() {
}

void GenerateCodeAction::Execute() {
	Output* pOut = pManager->GetOutput();
	string msg;
	if (!pManager->ValidateAll(msg)) {
		pOut->PrintMessage("Code Can't be Generated." + msg);
		return;
	}
	string filename;
	bool Gen = pManager->GenerateCode(filename,msg);
	if (Gen) {
		pOut->PrintMessage("Code generated successfully.");
	}
	else
	{
		pOut->PrintMessage(" Generation Failed ");
	}

}