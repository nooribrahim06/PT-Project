#include "Statement.h"

Statement::Statement()	
{ 
	//TODO: set the ID with a unique value
	Text = "";
	Selected = false;		
}

void Statement::SetSelected(bool s)
{	Selected = s; }

bool Statement::IsSelected() const
{	return Selected; }

void Statement::Simulate()
{
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

bool Statement::checkvar(varinfo vars[], int& varcount, string& msg)
{
	return true;
}

