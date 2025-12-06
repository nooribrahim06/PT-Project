#include "Write.h"
Write::Write(Point Lcorner,string& variable)
{
	var = variable;
	LeftCorner = Lcorner;
	pOutConn = NULL;	//No connectors yet
	UpdateStatementText();
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}
void Write::Draw(Output* pOut) const {
	pOut->DrawOutputStatement(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}
void Write::Save(ofstream& OutFile)
{
	return;
}
void Write::Load(ifstream& InFile)
{
	return;
}
void Write::Edit()
{
	// to be implemented
	return;
}
Statement* Write::Simulate(Input* pIn, Output* pOut)
{
	bool GVAL = false;
	double value = GetVar(var);
		pOut->PrintMessage(var + " = " + to_string(value));

	if (pOutConn != NULL)
	{
		return pOutConn->getDstStat();
	}
	else
	{
		return NULL;
	}




}



void Write::GenerateCode(ofstream& OutFile)
{
	// to be implemented
	return;
}

Point Write::GetOutletPoint() const
{
	return Outlet;
}
Point Write::GetInletPoint() const
{
	return Inlet;
}

Connector* Write::GetOutConnector() const
{
	return pOutConn;
}

void Write::SetOutconnector(Connector* C)
{
	pOutConn = C;
}

bool Write::IsPointInside(Point P) const
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

bool Write::Validate(varinfo vars[], int& varcount, string& msg)
{
	if (var.empty()) {
		msg = "Write statment doesn't have an expresson";
		return false;
	}
	OpType T = ValueOrVariable(var);
	if (T == VARIABLE_OP)
	{
		int idx = Findvarindex(var, vars, varcount);
		if (idx == -1 || !vars[idx].declared) {
			msg = "Variable " + var + " used without declaration.";
			return false;
		}
		if (!vars[idx].initialized) {
			msg = "Variable " + var + " used without initialization.";
			return false;
		}
	}
	else if (T == INVALID_OP)
	{
		msg = "Write statement has invalid expression '" + var + "' ";
		return false;
	}
	return true;
}
void Write::UpdateStatementText()
{
	Text = "Write " + var;
}
