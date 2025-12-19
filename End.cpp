#include "End.h"
#include <iostream>
#include <fstream>
using namespace std;
void End::UpdateStatementText()
{
	Text = "End";
}

End::End(Point Lcorner)
{
	Leftcorner = Lcorner;
	Inlet.x = Leftcorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = Leftcorner.y;
	Text = "End";
}

void End::Save(ofstream& OutFile)
{
	OutFile << "ENDS	" << GetstatementID() << "	" << Leftcorner.x << "	" << Leftcorner.y << endl;
	return;
}

void End::Load(ifstream& InFile)
{
	int id;
	InFile >> id>> Leftcorner.x >> Leftcorner.y;
	statementID = id;
	Inlet.x = Leftcorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = Leftcorner.y;
	UpdateStatementText();
	return;
}

void End::Edit()
{
	return;
}

Statement* End::Simulate(Input* pIn, Output* pOut)
{
	return this;
}


void End::GenerateCode(ofstream& OutFile)
{
	OutFile << "return 0;\n" << "}";
}
bool End::IsPointInside(Point P) const
{
	bool insideX = (P.x >= Leftcorner.x) && (P.x <= Leftcorner.x + UI.ASSGN_WDTH);
	bool insideY = (P.y >= Leftcorner.y) && (P.y <= Leftcorner.y + UI.ASSGN_HI);
	return (insideX && insideY);
}
Point End::GetOutletPoint() const
{
	// End statement has no outlet point
	return Point(-1, -1); // Indicate no outlet point
}
Point End::GetInletPoint() const
{
	return Inlet;
}
Connector* End::GetOutConnector() const
{
	return nullptr;
}
void End::SetOutconnector(Connector* C)
{
	// should not be called
}
bool End::IsEnd() const
{
	return true;
}
bool End:: Validate(varinfo vars[], int& varcount, string& msg) 
{
	return true;
}
void End::Draw(Output* pOut) const
{
	pOut->DrawEnd(Leftcorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}
Statement* End::Clone() const {
	// 1) Create a new object by copying *this*pa
	End* c = new End(*this);  // uses default copy ctor

	// 2) Fix any pointer members so they don't share stuff
	c->SetOutconnector(nullptr);   // NO connectors are copied

	// 3) A copied statement should not start as "selected"
	c->SetSelected(false);

	// 4) Return it as a Statement*
	return c;
}

void End::Move(const Point& P)
{
	Leftcorner = P;
	Inlet.x = Leftcorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = Leftcorner.y;
}
