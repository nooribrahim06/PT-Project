#include "Start.h"

Start::Start(Point Lcorner)
{
	// Constructor implementation here
	LeftCorner = Lcorner;
	Outlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
	Text = "Start";
}
void Start::Draw(Output* pOut) const
{
	// Implementation here
	pOut->DrawStart(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}

void Start::Save(ofstream& OutFile)
{
}

void Start::Load(ifstream& InFile)
{
}

void Start::Simulate()
{
}

void Start::GenerateCode(ofstream& OutFile)
{
	// to be implemented
}

bool Start::IsStart() const
{
	return true;
}

bool Start::Validate(varinfo vars[], int& varcount, string& msg)
{
	return true;
}
