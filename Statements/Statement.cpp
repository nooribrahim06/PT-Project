#include "Statement.h"

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

void Statement::Simulate()
{
	return;
	// to be implemented 
}

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

