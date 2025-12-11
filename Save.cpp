#include "Save.h"
#include "ApplicationManager.h"
#include "GUI/Output.h"
#include "GUI/Input.h"
#include "GUI/UI_Info.h"
#include <iostream>
#include <fstream>
using namespace std;

Save::Save(ApplicationManager* pAppManager) : Action(pAppManager)
{
}

void Save::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Save: Enter File name without Extension (.txt)");
	string fname = pIn->GetString(pOut);
	FileName = fname + ".txt";
}

void Save::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	ofstream file(FileName);
	if (!file)
	{
		pOut->PrintMessage("File Can't Be Opened");
		return;
	}
	pManager->SaveAll(file);
	pOut->PrintMessage("FlowChart Saved successfully.");
}
