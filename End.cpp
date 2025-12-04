#include "End.h"

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
	return;
}

void End::Load(ifstream& InFile)
{
	return;
}

void End::Edit()
{
	return;
}

void End::Simulate()
{
	return;
}
void End::GenerateCode(ofstream& OutFile)
{
	// to be implemented
	return;
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
bool End::Validate(varinfo vars[], int& varcount, string& msg)
{
	return true;
}
void End::Draw(Output* pOut) const
{
	pOut->DrawEnd(Leftcorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}
