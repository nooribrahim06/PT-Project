#include "End.h"

End::End(Point Lcorner)
{
	Leftcorner = Lcorner;
	Inlet.x = Leftcorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = Leftcorner.y;
	Text = "End";
}

void End::Save(ofstream& OutFile)
{
}

void End::Load(ifstream& InFile)
{
}

void End::Simulate()
{
}
void End::GenerateCode(ofstream& OutFile)
{
	// to be implemented
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
