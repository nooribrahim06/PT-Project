#include "Read.h"

Read::Read(Point Lcorner, const string& var)
{
	this->var = var;
	LeftCorner = Lcorner;
	pOutConn = NULL;	//No connectors yet
	UpdateStatementText();

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}
void Read::Draw(Output* pOut) const
{
	pOut->DrawInputStatement(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}
void Read::Save(ofstream& OutFile)
{
	// to be implemented 
}
void Read::Load(ifstream& InFile)
{
	// to be implemented
}
void Read::Edit()
{
	// to be implemented
}
void Read::Simulate()
{
	// 
}

