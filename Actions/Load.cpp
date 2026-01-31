#include "Load.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Output.h"
#include "..\GUI\Input.h"
#include "..\GUI\UI_Info.h"
#include <iostream>
#include <fstream>
using namespace std;
Load::Load(ApplicationManager* pAppManager) : Action(pAppManager)
{
}

void Load::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Load: Enter File name without Extension (.txt)");
	string fname = pIn->GetString(pOut);
	FileName = fname + ".txt";
}

void Load::Execute()
{
	pManager->UpdateInterface();
	Output* pOut = pManager->GetOutput();
	pOut->ClearDrawArea();
	
	ReadActionParameters();

	ifstream file(FileName);
	if (!file) {
		pOut->PrintMessage("File Can't be Opened");
		return;
	}
	 pManager->LoadAll(file);
	 pManager->UpdateInterface();
	 pOut->PrintMessage("FlowChart Loaded successfully.");
	 
}
