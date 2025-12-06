#include "ApplicationManager.h"
#include "Actions\AddValueAssign.h"
#include "AddStart.h"
#include "AddEnd.h"
#include "AddCondition.h"
#include "AddDeclare.h"
#include "AddOperAssign.h"
#include "AddVarAssign.h"
#include "AddRead.h"
#include "AddWrite.h"
#include "AddConnect.h"
#include "Select.h"
#include "GUI\Input.h"
#include "GUI\Output.h"
#include "ValidateAction.h"
#include"GenerateCodeAction.h"
#include"DebugRunAction.h"
#include"RunAction.h"
#include"SwitchtoDesignAction.h"



//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	StatCount = 0;
	ConnCount = 0;
	pSelectedStat = NULL;	//no Statement is selected yet
	pSelectedConn = NULL;
	pClipboard = NULL;
	
	//Create an array of Statement pointers and set them to NULL		
	for(int i=0; i<MaxCount; i++)
	{
		StatList[i] = NULL;	
		ConnList[i] = NULL;
	}
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//


ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to ActioType, create the corresponding action object
	switch (ActType)
	{
		case ADD_START:
			pAct = new AddStart(this);
			break;
		case ADD_END:
			pAct = new AddEnd(this);
			break;
		case ADD_DECLARE_VARIABLE:
			pAct = new AddDeclare(this);
			break;
		case ADD_VALUE_ASSIGN:
			pAct = new AddValueAssign(this);
			break;
		case ADD_VAR_ASSIGN:
			pAct = new AddVarAssign(this);
			break;
		case ADD_OPER_ASSIGN:
			pAct = new AddOperAssign(this);
			break;
		case ADD_CONDITION:
			///create AddCondition Action here
			pAct = new AddCondition(this);
			break;
		case ADD_READ:
			pAct = new AddRead(this);
			break;
		case ADD_WRITE:
			pAct = new AddWrite(this);
			break;
		case VALIDATE:
			pAct = new ValidateAction(this);
			break;
		case GENERATE_CODE:
			pAct = new GenerateCodeAction(this);
			break;
		case RUN:
			pAct = new RunAction(this);
			break;
		case DEBUG_RUN:
			pAct = new DebugRunAction(this);
			break;
		case SWITCH_DSN_MODE:
			pAct = new SwitchtoDesignAction(this);
			break;
		case SWITCH_SIM_MODE:
		
		case ADD_CONNECTOR:
			pAct = new AddConnect(this);
			break;
		case SELECT:
			///create Select Action here
			pAct = new Select(this);
			break;
		
		case EXIT1:
			///create Exit Action here
			
			break;
		
		case STATUS:
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
	}
}



//==================================================================================//
//						Statements Management Functions								//
//==================================================================================//


//Add a statement to the list of statements
void ApplicationManager::AddStatement(Statement *pStat)
{
	if(StatCount < MaxCount)
		StatList[StatCount++] = pStat;
	
}

////////////////////////////////////////////////////////////////////////////////////
Statement *ApplicationManager::GetStatement(Point P) const
{
	//If this point P(x,y) belongs to a statement return a pointer to it.
	//otherwise, return NULL


	///Add your code here to search for a statement given a point P(x,y)	
	///WITHOUT breaking class responsibilities
	for(int i=0; i<StatCount; i++)
	{
		if(StatList[i]->IsPointInside(P))
			return StatList[i];
	}

	return NULL;
}
////////////////////////////////////////////////////////////////////////////////////
//Returns the selected statement
Statement *ApplicationManager::GetSelectedStatement() const
{	return pSelectedStat;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the statement selected by the user
void ApplicationManager::SetSelectedStatement(Statement *pStat)
{	pSelectedStat = pStat;	}

////////////////////////////////////////////////////////////////////////////////////
//Returns the Clipboard
Statement *ApplicationManager::GetClipboard() const
{	return pClipboard;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the Clipboard
void ApplicationManager::SetClipboard(Statement *pStat)
{	pClipboard = pStat;	}

Connector* ApplicationManager::GetSelectedConn() const
{
	return pSelectedConn;
}

void ApplicationManager::SetSelectedConn(Connector* pConn)
{
	pSelectedConn = pConn;
}


//N: Add Connector to the list of connectors
void ApplicationManager::AddConnector(Connector* pConn)
{
	if (ConnCount < MaxCount)
		ConnList[ConnCount++] = pConn;
}
Connector* ApplicationManager::GetConnector(Point P) const
{
	//If this point P(x,y) belongs to a connector return a pointer to it.
	//otherwise, return NULL
	// to be implemented later
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i]->IsPointInside(P))
			return ConnList[i];
	}

	return NULL;
}

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//


//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();

	//Draw all statements
	for(int i=0; i<StatCount; i++)
		StatList[i]->Draw(pOut);
	
	//Draw all connections
	for(int i=0; i<ConnCount; i++)
		ConnList[i]->Draw(pOut);

}
bool ApplicationManager::ValidateAll(string& msg)
{
	Statement* startStat = nullptr;
	Statement* endStat = nullptr;
	// Find Start and End statements
	int stcount = 0, endcount = 0;
	
	for (int i = 0; i < StatCount; i++)
	{
		Statement * stat = StatList[i];
		if (!stat)
		{
			continue;
		}
		if (stat->IsStart()) {
			startStat = StatList[i];
			stcount++;
		}
		if (stat->IsEnd()) {
			endStat = StatList[i];
			endcount++;
		}

	}
	if (stcount != 1)
	{
		msg = "Flowchart must have one Start statement.";
		return false;
	}
	if (endcount != 1)
	{
		msg = "Flowchart must have one End statement.";
		return false;
	}
	
	// Now for the connectors//
	for (int i = 0; i < ConnCount; i++)
	{
		Connector* CO = ConnList[i];
		if (!CO)
		{
			continue;
		}
		if (CO->getDstStat() == nullptr || CO->getSrcStat() == nullptr)
		{
			msg = " Error: Free Connector (Missing Source Or Destination)";
			return false;
		}
			
	}
// legal connectors //
	for(int j=0;j<StatCount;j++) {
		int inc = 0, Otc = 0;
		Statement* stat = StatList[j];
		if (!stat)
		{
			continue;
		}
		// count incoming and outcoming connectors //
		for (int i = 0; i < ConnCount; i++)
		{
			Connector* CO = ConnList[i];
			if(!CO)
			{
				continue;
			}
			if (CO->getSrcStat()==stat) Otc++;
			if (CO->getDstStat() == stat) inc++;
		}
		if (stat->IsStart()) {
			if (inc != 0 || Otc != 1) {
			   msg = " Start statement can't have incoming connectors or more than one outgoing connector.";
			return false;
			}
		}
		else if (stat->IsEnd()) {
				if (inc != 1 || Otc != 0) {
					msg = " End statement can't have outgoing connectors or more than one incoming connector.";
					return false;
				}
			}

		else if (stat->Isconditional()) {
			if(inc!=1|| Otc != 2) {
				msg = " Conditional statement must have one incoming and two outgoing connectors.";
				return false;
			}


		}
		else {
			if (inc < 1 || Otc != 1) {
				msg = " Each statement must have at least one incoming and one outgoing connector.";
				return false;
		    }
		}
	}
	//Check for the Variable Validation//
	varinfo vars[MaxCount];
	int varcount = 0;
	for (int i = 0; i < MaxCount; i++) {
		vars[i].declared = false;
		vars[i].name = "";
		vars[i].initialized = false;
	}
	for (int j = 0; j < StatCount; j++) {
		Statement* stat = StatList[j];
		if (!stat)
		{
			continue;
		}
		if (!stat->Validate(vars, varcount, msg)) {
			return false;
		}
	}

	msg = " Valid Flowchart";
	return true;
}

bool ApplicationManager::Run(string& msg)
{
	if (!ValidateAll(msg))
	{
		msg = "Error : Cannot Run the Flowchart. " + msg;
		return false;
	}
	varCount = 0;
	for (int i = 0; i < 200; i++)
	{
		VarIntial[i] = false;
	}
	Statement* cur = NULL;
	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i] && StatList[i]->IsStart())
		{
			cur = StatList[i];
			break;
		}
	}
	if (cur == NULL)
	{
		msg = "Error no Start Statement .";
		return false;
	}
	Input* pIn = GetInput();
	Output* pOut = GetOutput();

	int count = 0;
	const int Steps = 500;
	while (cur && !cur->IsEnd())
	{
		cur = cur->Simulate(pIn, pOut);
		if (!cur) {
			msg = "Missing connector or invalid next Statment";
			return false;
		}
		count++;
		if (count > Steps)
		{
			msg = "Error :No End Statement";
			return false;
		}
	}
	if (cur == NULL)
	{
		msg = "Error ";
		return false;
	}
	msg = "Run finished successfully";
	return true;
}

bool ApplicationManager::Debug(string& msg)
{
	if (!ValidateAll(msg))
	{
		msg = "Error : Cannot Run the Flowchart. " + msg;
		return false;
	}
}

bool ApplicationManager::GenerateCode(const string& filename, string& msg)
{
	/*ofstream out(filename);*/
}


////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////


//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<StatCount; i++)
		delete StatList[i];
	for(int i=0; i<ConnCount; i++)
		delete ConnList[i];
	delete pIn;
	delete pOut;
	
}
