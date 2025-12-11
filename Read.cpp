#include "Read.h"

Read::Read(Point Lcorner, const string& var)
{
	this->varName = var;
	LeftCorner = Lcorner;
	pOutConn = NULL;	//No connectors yet
	UpdateStatementText();

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}
void Read::Draw(Output* pOut) const
{
	pOut->DrawInputStatement(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}
void Read::Save(ofstream& OutFile)
{
	// to be implemented 
	return;
}
void Read::Load(ifstream& InFile)
{
	// to be implemented
	return;
}
void Read::Edit()
{
	// to be implemented
	return;
}
Statement* Read::Simulate(Input* pIn, Output* pOut)
{
	pOut->PrintMessage("Enter the value for " + varName + ":");
	double value = pIn->GetValue(pOut);
	 Statement::SetVar(varName, value);
	 Connector* pOutConn = GetOutConnector();
	if (pOutConn != NULL)
	{
		return pOutConn->getDstStat();
	}
	else
	{
		return NULL;
	}
}

void Read::GenerateCode(ofstream& OutFile)
{
	// to be implemented
	return;
}
Point Read::GetOutletPoint() const
{
	return Outlet;
}
Point Read::GetInletPoint() const
{
	return Inlet;
}
Connector* Read::GetOutConnector() const
{
	return pOutConn;
}
void Read::SetOutconnector(Connector* C)
{
	pOutConn = C;
}
bool Read::IsPointInside(Point P) const
{
	int W = UI.ASSGN_WDTH;
	int H = UI.ASSGN_HI;
	int shift = W / 4;

	// ===== case 1: central rectangle =====
	if (P.x >= LeftCorner.x + shift && P.x <= LeftCorner.x + W &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + H)
		return true;

	// ===== case 2: left slanted part =====
	if (P.x >= LeftCorner.x && P.x < LeftCorner.x + shift &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + H)
	{
		// line from (Left, top) to (Left+shift, bottom)
		double slope = double(H) / double(shift);
		double y_left = LeftCorner.y + slope * (P.x - LeftCorner.x);

		// inside = between slanted edge and bottom
		if (P.y >= y_left && P.y <= LeftCorner.y + H)
			return true;
	}

	// ===== case 3: right slanted part =====
	if (P.x > LeftCorner.x + W && P.x <= LeftCorner.x + W + shift &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + H)
	{
		// right edge: from (Left+W, top) to (Left+W+shift, bottom)
		double slope = double(H) / double(shift);
		double y_right = LeftCorner.y + slope * (P.x - (LeftCorner.x + W));

		// inside = between that slanted edge and bottom
		if (P.y >= y_right && P.y <= LeftCorner.y + H)
			return true;
	}

	return false;

}
void Read::UpdateStatementText()
{
	Text = "Read " + varName;
}

bool Read::Validate(varinfo vars[], int& varcount, string& msg)
{
	if (varName.empty()) {
		msg = "The variable name in Read statement is empty";
		return false;
	}
	if (!IsVariable(varName)) {
		msg = "Read statement variable '" + varName + "' is not a valid variable name.";
		return false;
	}
	int idx = Findvarindex(varName, vars, varcount);
	if (idx == -1 || !vars[idx].declared) {
		msg = "Variable " + varName + " used without declaration.";
		return false;
	}
	else {
		vars[idx].initialized = true;
		return true;

	}
}
