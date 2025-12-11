#include "DebugRunAction.h"
#include "ApplicationManager.h"
#include "Statements\Statement.h"

DebugRunAction::DebugRunAction(ApplicationManager* pAppManager):Action(pAppManager)
{
}
void DebugRunAction::ReadActionParameters() {


}
void DebugRunAction::Execute() {
	
	Input* pIn = pManager-> GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->ClearOutputBar();
	Statement* cur = nullptr;
	string msg;
	if (!pManager->Debug(msg, cur)) {
		pOut->PrintMessage(msg);
		return;
	}
	int count = 0;
	const int Steps = 1000;
	while (cur && !cur->IsEnd())

	{
		Statement* Next = cur;
		cur = cur->Simulate(pIn, pOut);
		if (!cur) {
			msg = "Missing connector or invalid next Statment";
			return;
		}
		count++;
		if (count > Steps)
		{
			msg = "Error :No End Statement";
			return;
		}

		string debugInfo = Statement::GetDebug_RunVars();

		string outmsg = "Debug Info:  " + debugInfo + "\n Click to continue";
		pOut->PrintMessage(outmsg);
		Next->SetSelected(true);
		pManager->UpdateInterface();
		Point Click;
		pIn->GetPointClicked(Click);
		Next->SetSelected(false);

	}
	if (cur == NULL)
	{
		msg = "Error: FLowchart terminated without reaching End ";
		return;
	}

	string out = Statement::GetDebug_RunVars();
	pOut->PrintMessage("Program Ended Successfully. \n Variables: " + out);
}
	

