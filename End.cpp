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
void End::Draw(Output* pOut) const
{
	pOut->DrawEnd(Leftcorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}
