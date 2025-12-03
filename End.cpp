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
bool End::IsEnd() const
{
	return true;
}
void End::Draw(Output* pOut) const
{
	pOut->DrawEnd(Leftcorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}
