#include "Exit.h"
#include "ApplicationManager.h"
Exit::Exit(ApplicationManager* pAppManager) 
	: Action(pAppManager)
{
}
void Exit::ReadActionParameters() 
{
	// No parameters to read
}
void Exit::Execute() 
{
	// No specific execution code needed to exit the application
	// just clear what destructors will handle
	pManager->GetOutput()->PrintMessage("Exiting the application...");
	pManager->ClearAll();
}
