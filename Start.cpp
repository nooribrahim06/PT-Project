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
	pOutConn = NULL;
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

Point Start::GetOutletPoint() const
{
	return Outlet;
}
Point Start::GetInletPoint() const
{
	// Start has no inlet point
	return Point(-1, -1); // or some invalid point
}

Connector* Start::GetOutConnector() const
{
	return pOutConn;
}

void Start::SetOutconnector(Connector* C)
{
	pOutConn = C;
}

bool Start::IsStart() const
{
	return true;
}

bool Start::IsPointInside(Point P) const
{
	if( P.x >= LeftCorner.x && P.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.ASSGN_HI)
	{
		return true;
	}
	return false;
}

bool Start::Validate(varinfo vars[], int& varcount, string& msg)
{
	return true;
}
