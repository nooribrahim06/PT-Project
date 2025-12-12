#include "Start.h"
#include "ApplicationManager.h"
#include "Actions/Action.h"
#include <iostream>
#include <fstream>
using namespace std;
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
	OutFile << "STRT	" << GetstatementID() << "	" << LeftCorner.x << "	" << LeftCorner.y << "	" << endl;
	return;
}

void Start::Load(ifstream& InFile)
{
	return;
}

//void Start::Edit()
//{
//	pOut->PrintMessage("Start statement cannot be edited.");
//	return;
//}

Statement* Start::Simulate(Input* pIn, Output* pOut)
{
	Connector* pOutConn = GetOutConnector();
	if (pOutConn != NULL)
	{
		return pOutConn->getDstStat();
	}
	else {
		return NULL;
	}
}


void Start::GenerateCode(ofstream& OutFile)
{
	OutFile << "#include <iostream>\n";
	OutFile << "#include <cmath>\n";
	OutFile << "using namespace std;\n";
	OutFile << "int main () {\n";
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

bool Start::Validate(varinfo vars[], int& varcount, string& msg) {
	return true;
}

Statement* Start::Clone() const 
{
	Start* copy = new Start(*this);
	copy->SetOutconnector(nullptr);
	copy->SetSelected(false);
	return copy;
}

void Start::Move(const Point& P) 
{
	LeftCorner = P;
	Outlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}