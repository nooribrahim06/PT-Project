#include "Start.h"

void Start::UpdateStatementText()
{
	Text = "Start";
}

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
	return;
}

void Start::Load(ifstream& InFile)
{
	return;
}

void Start::Edit()
{
	return;
}

void Start::Simulate()
{
	return;
}

void Start::GenerateCode(ofstream& OutFile)
{
	// to be implemented
	return;
}

bool Start::IsStart() const
{
	return true;
}

bool Start::Validate(varinfo vars[], int& varcount, string& msg)
{
	return true;
}
