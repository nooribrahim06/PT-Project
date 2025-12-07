#include "SwitchToSim.h"
#include "ApplicationManager.h"
#include "GUI/Output.h"


SwitchToSim::SwitchToSim(ApplicationManager* pManager) : Action(pManager) {}
void SwitchToSim::Execute() {
	Output* pOut = pManager->GetOutput();
	pOut->CreateSimulationToolBar();
}
void SwitchToSim::ReadActionParameters() {

}
