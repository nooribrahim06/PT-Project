#include "Statement.h"

//string* VarNames=nullptr;
//double *VarValues = nullptr;
//bool *VarIntial = nullptr;
// int varCount =0 ;

//void SetVar(const string& name, double value)
//{
//	for (int i = 0; i < varCount; i++) {
//		if (VarNames[i] == name)
//		{
//			VarValues[i] = value;
//			VarIntial[i] = true;
//			return;
//		}
//	}
//	if (varCount < 200)
//	{
//		VarNames[varCount] = name;
//		VarValues[varCount] = value;
//		VarIntial[varCount] = true;
//		varCount++;
//	}
//}
//
//double GetVar(const string& name)
//{
//	for (int i = 0; i < varCount; i++)
//	{
//		if (VarNames[i] == name)
//		{
//			
//			return VarValues[i];
//		}
//	}
//	
//	return 0.0;
//}

int Statement::ID = 1; //Initialize static ID variable
string Statement::R_names[Statement::Maxrunvars];
double Statement::R_values[Statement::Maxrunvars]; // copied from chat needs to be written//
int    Statement::R_count = 0;

string Statement::GetDebug_RunVars()
{
	string msg = "";
	if (R_count == 0)
	{
		msg = "No Variabes.";
			return msg;
	}
	for (int i = 0; i < R_count; ++i)
	{
		msg += R_names[i] + " = " + to_string(R_values[i]) + "\n";
		if (i < R_count - 1) {
			msg += " , ";
		}
	}
		return msg;
}

void Statement::Resetrunvars()
{
	R_count = 0;
	for (int i = 0; i < Maxrunvars; ++i)
	{
		R_names[i].clear(); // copied from chat needs to be written//
		R_values[i] = 0;

	}
}
void Statement::SetVar(const string& name, double value)
{
	for (int i = 0; i < R_count; i++) {
		if (R_names[i] == name)
		{
			R_values[i] = value;
			return;
		}
	}
	if (R_count < Maxrunvars)
	{
		R_names[R_count] = name;
		R_values[R_count] = value;
		R_count++;
}
}

double Statement::GetVar(const string& name)
{
	for (int i = 0; i < R_count; i++)
	{
		if (R_names[i] == name)
		{

			return R_values[i];
		}
	}

	return 0;
	}
	// If you reach here, something is wrong with Validate or flowchart

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

