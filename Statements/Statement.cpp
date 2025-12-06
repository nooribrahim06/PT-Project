#include "Statement.h"

string VarNames[200];
double VarValues[200];
bool VarIntial[200];
int varCount = 0;

void SetVar(const string& name, double value)
{
	for (int i = 0; i < varCount; i++) {
		if (VarNames[i] == name)
		{
			VarValues[i] = value;
			VarIntial[i] = true;
			return;
		}
	}
	if (varCount < 200)
	{
		VarNames[varCount] = name;
		VarValues[varCount] = value;
		VarIntial[varCount] = true;
		varCount++;
	}
}

double GetVar(const string& name)
{
	for (int i = 0; i < varCount; i++)
	{
		if (VarNames[i] == name)
		{
			
			return VarValues[i];
		}
	}
	
	return 0.0;
}

int Statement::ID = 1; //Initialize static ID variable

Statement::Statement()	
{ 
	//TODO: set the ID with a unique value
	Text = "";
	statementID = ID++;
	Selected = false;		
}

int Statement::GetstatementID() const
{
	return statementID;
}

void Statement::SetSelected(bool s)
{	Selected = s; }

bool Statement::IsSelected() const
{	return Selected; }



bool Statement::IsStart() const
{
	return false;
}

bool Statement::IsEnd() const
{
	return false;
}

bool Statement::Isconditional() const
{
	return false;
}

bool Statement::Validate(varinfo vars[], int& varcount, string& msg)
{
	return true;
}

Statement::~Statement()
{	
}

