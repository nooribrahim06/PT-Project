#include "GenerateCodeAction.h"
#include "ApplicationManager.h"
#include "GUI/Output.h"
#include "GUI/Input.h"
#include "GUI/UI_Info.h"
#include <fstream>
using namespace std;
GenerateCodeAction::GenerateCodeAction(ApplicationManager* pAppManager):Action(pAppManager)
{
}
void GenerateCodeAction::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Generate Code: Enter File name without Extension (.cpp)");
	string filename_without_extension = pIn->GetString(pOut);
	FileName = filename_without_extension + ".cpp";
}

void GenerateCodeAction::Execute() {
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	string msg;
	if (!pManager->ValidateAll(msg)) {
		pOut->PrintMessage("Code Can't be Generated." + msg);
		return;
	}
	ofstream file(FileName);
	if (!file)
	{
		pOut->PrintMessage("File Can't be Opened!");
	}
	bool Gen = pManager->GenerateCode(file,msg);
	if (Gen) {
		pOut->PrintMessage("Code generated successfully.");
	}
	else
	{
		pOut->PrintMessage(" Generation Failed ");
	}

}