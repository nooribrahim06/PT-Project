#include "End.h"

End::End(Point Lcorner)
{
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
void End::Draw(Output* pOut) const
{
	//pOut->DrawEnd(Leftcorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}
