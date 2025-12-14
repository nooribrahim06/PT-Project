#include "ApplicationManager.h"
#include "Actions\AddValueAssign.h"
#include "AddStart.h"
#include "AddEnd.h"
#include "AddCondition.h"
#include "Condition.h"
#include "AddDeclare.h"
#include "AddOperAssign.h"
#include "AddVarAssign.h"
#include "AddRead.h"
#include "AddWrite.h"
#include "AddConnect.h"
#include "Connector.h"
#include "Select.h"
#include "Copy.h"
#include "Paste.h"
#include "Cut.h"
#include "Delete.h"
#include "GUI\Input.h"
#include "GUI\Output.h"
#include "Edit.h"
#include "ValidateAction.h"
#include "GenerateCodeAction.h"
#include "DebugRunAction.h"
#include "RunAction.h"
#include "SwitchtoDesignAction.h"
#include "SwitchToSim.h"
#include "Save.h"
#include <fstream>

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
		case EDIT_STAT:
			pAct = new Edit(this);
			break;
		case SAVE:
			pAct = new Save(this);
			break;
		case COPY:
			pAct = new Copy(this);
			break;
		case PASTE:
			pAct = new Paste(this);
			break;
		case CUT:
			pAct = new Cut(this);
			break;
		case DEL:
			pAct = new Delete(this);
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
			pAct = new SwitchToSim(this);
			break;
		case ADD_CONNECTOR:
			pAct = new AddConnect(this);
			break;
		case SELECT:
			///create Select Action here
			pAct = new Select(this);
			break;
		
		case EXIT:
			///create Exit Action here
			
			break;
		
		case STATUS:
			UpdateInterface();
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
void ApplicationManager::DeleteConnector(Connector* pConn)
{
	if (!pConn) return;
	//remove highlight and select pointer
	pConn->Setselected(false);
	if (pSelectedConn == pConn)
	{
		pSelectedConn = nullptr;
	}

	Statement* src = pConn->getSrcStat();

	//detach from source statement

	if (src)
	{
		if (src->Isconditional())
		{
			Condition* cond = dynamic_cast<Condition*>(src);
			if (cond)
			{
				if (cond->GetTrueConn() == pConn) cond->SetTrueConn(nullptr);
				if (cond->GetFalseConn() == pConn) cond->SetFalseConn(nullptr);
			}
		}
		else
		{

			if (src->GetOutConnector() == pConn)
			{
				src->SetOutconnector(nullptr);
			}
		}
	}

	// Find and delete the connector from ConnList
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i] == pConn)
		{
			delete ConnList[i];
			// Shift connectors left
			for (int j = i; j < ConnCount - 1; j++)
			{
				ConnList[j] = ConnList[j + 1];
			}
			ConnList[--ConnCount] = nullptr;
			break;
		}
	}
	// Clear selection if it was the deleted connector
	if (pSelectedConn == pConn) pSelectedConn = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::DeleteStatementWithConnectors(Statement* s)
{
	if (!s) 
		return;

	//deselect the statement
	s->SetSelected(false);;
	if (pSelectedStat == s)
	{
		pSelectedStat = nullptr;
	}

	if (pSelectedConn)
	{
		Statement* s = pSelectedConn->getSrcStat();
		Statement* d = pSelectedConn->getDstStat();
		if (s == s || d == s)
			pSelectedConn = nullptr;
	}

	// delete all incoming connectors
    for (int i = 0; i < ConnCount; )
	{
		Connector* conn = ConnList[i];
		if (!conn)
		{
			i++;
			continue;
		}

		Statement* src = conn->getSrcStat();
		Statement* dst = conn->getDstStat();

		if (src == s || dst == s)
		{
			if (src ==s)
			{
				s->SetOutconnector(nullptr);
			}
			
			delete conn;
			// Shift connectors left
			for (int j = i; j < ConnCount - 1; j++)
			{
				ConnList[j] = ConnList[j + 1];
			}
			ConnList[--ConnCount] = nullptr;
			continue; //recheck same index after shift
		}

		i++;
	}

	// Then, delete the statement itself from StatList

    for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i] == s)
		{
			delete StatList[i];
			// Shift statements left
			for (int j = i; j < StatCount - 1; j++)
			{
				StatList[j] = StatList[j + 1];
			}
			StatList[--StatCount] = nullptr;
			break;
		}
	}

	//clear selection if it was the deleted statement
	if (pSelectedStat == s) pSelectedStat = nullptr;
}
////////////////////////////////////////////////////////////////////////////////////

//Returns the Clipboard
Statement *ApplicationManager::GetClipboard() const
{	return pClipboard;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the Clipboard
void ApplicationManager::SetClipboard(Statement *pStat)
{	pClipboard = pStat;	}
////////////////////////////////////////////////////////////////////////////////////
//Clears the Clipboard
void ApplicationManager::ClearClipboard()
{
	if(pClipboard)
	{
		delete pClipboard;
		pClipboard = NULL;	
	}
}
////////////////////////////////////////////////////////////////////////////////////

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
	// 1) redraw UI chrome (toolbar/status/output panel)
	if (UI.AppMode == DESIGN)
		pOut->CreateDesignToolBar();
	else
		pOut->CreateSimulationToolBar();

	pOut->CreateStatusBar();

	pOut->ClearOutputBar();
	pOut->ClearDrawArea();

	// 2) draw all statements
	for (int i = 0; i < StatCount; i++)
		if (StatList[i]) StatList[i]->Draw(pOut);

	// 3) draw all connections
	for (int i = 0; i < ConnCount; i++)
		if (ConnList[i]) ConnList[i]->Draw(pOut);

	// 4) if you enable buffering, push it to screen
	// pOut->GetWindow()->UpdateBuffer();  // only if you added GetWindow()
}
bool ApplicationManager::ValidateAll(string& msg)
{
	Statement* startStat = nullptr;
	Statement* endStat = nullptr;
	// Find Start and End statements
	int stcount = 0, endcount = 0;
	int startidx = -1;

	for (int i = 0; i < StatCount; i++)
	{
		Statement* stat = StatList[i];
		if (!stat)
		{
			continue;
		}
		if (stat->IsStart()) {
			startStat = StatList[i];
			stcount++;
			startidx = i;
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
	for (int j = 0; j < StatCount; j++) {
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
			if (!CO)
			{
				continue;
			}
			if (CO->getSrcStat() == stat) Otc++;
			if (CO->getDstStat() == stat) inc++;
		}
		if (stat->IsStart()) {
			if (inc != 0 || Otc != 1) {
				msg = " Start statement can't have incoming connectors or more than one outgoing connector.";
				return false;
			}
		}
		else if (stat->IsEnd()) {
			if (inc < 1 || Otc != 0) {
				msg = " End statement can't have outgoing connectors or more than one incoming connector.";
				return false;
			}
		}

		else if (stat->Isconditional()) {
			if (inc != 1 || Otc != 2) {
				msg = " Conditional statement must have one incoming and two outgoing connectors.";
				return false;
			}


		}
		else {
			if (inc < 1 || Otc != 1) {
				msg = " Statement must have at least one incoming and one outgoing connector.";
				return false;
			}
		}
	}
	varinfo vars[200];   // same size you used elsewhere
	int varcount = 0;
	for (int i = 0; i < 200; ++i) {
		vars[i].name = "";
		vars[i].declared = false;
		vars[i].initialized = false;
	}
	// ============ 4) BFS from Start, following connectors ============
	//const int MAX_STMTS = 200;   // must be >= StatList capacity

	Statement* Q[MaxCount];
	bool visited[MaxCount];

	for (int i = 0; i < MaxCount; ++i)
		visited[i] = false;

	int front = 0, back = 0;

	Q[back++] = startStat;
	visited[startidx] = true;

	while (front < back)
	{
		Statement* cur = Q[front++];

		// 4.1) Validate this statement with current vars table
		if (!cur->Validate(vars, varcount, msg))
		{
			// msg already filled by the statement
			return false;
		}

		// 4.2) Follow all connectors that go out of this statement
		for (int c = 0; c < ConnCount; ++c)
		{
			Connector* conn = ConnList[c];
			if (!conn)
				continue;

			if (conn->getSrcStat() != cur)
				continue;

			Statement* next = conn->getDstStat();
			if (!next)
				continue;

			// find index of next in StatList
			int nextIdx = -1;
			for (int i = 0; i < StatCount; ++i)
			{
				if (StatList[i] == next)
				{
					nextIdx = i;
					break;
				}
			}
			if (nextIdx == -1)
				continue;   // should not happen if StatList is consistent

			if (!visited[nextIdx])
			{
				visited[nextIdx] = true;
				Q[back++] = next;
			}
		}
	}

	// ============ 5) Check for unreachable statements ============
	for (int i = 0; i < StatCount; ++i)
	{
		if (!StatList[i])
			continue;

		if (!visited[i])
		{
			msg = "Flowchart has unreachable statements (not reachable from Start).";
			return false;
		}
	}

	msg = " Valid Flowchart";
	return true;
}


bool ApplicationManager::Run(string& msg)
{
	Input* pIn = GetInput();
	Output* pOut = GetOutput();

	if (!ValidateAll(msg))
	{
		msg = "Error : Cannot Run the Flowchart. " + msg;
		return false;
	}

	Statement::Resetrunvars();

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

	int count = 0;
	const int Steps = 1000;
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
		msg = "Error: FLowchart terminated without reaching End ";
		return false;
	}

	return true;
}

bool ApplicationManager::Debug(string& msg, Statement*& cur)
{
	if (!ValidateAll(msg))
	{
		msg = "Error : Cannot Debug the Flowchart. " + msg;
		return false;
	}

	Statement::Resetrunvars();
	cur = NULL;
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



	return true;
}

bool ApplicationManager::GenerateCode(ofstream& file, string& msg)
{
	Statement* current = nullptr;
	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i] && StatList[i]->IsStart())
		{
			current = StatList[i];
			break; // we found it, stop
		}
	}
	if (!current)
	{
		msg = "No START statement found.";
		return false;
	}

	while (true)
	{
		if (current->IsEnd())
		{
			current->GenerateCode(file);
			break;
		}
		current->GenerateCode(file);
		if (current->Isconditional())
		{

			Condition* TempCond = dynamic_cast<Condition*>(current);
			Statement* trueStart = TempCond->GetTrueConn()->getDstStat();
			Statement* falseStart = TempCond->GetFalseConn()->getDstStat();

			bool trueIsEmpty = trueStart->IsEnd();
			bool falseIsEmpty = falseStart->IsEnd();
			Statement* condition_road = TempCond->GetTrueConn()->getDstStat();
			file << "{\n";
			if (!trueIsEmpty)
			{
				// TRUE branch
				while (!condition_road->IsEnd())
				{
					condition_road->GenerateCode(file);
					condition_road = condition_road->GetOutConnector()->getDstStat();
				}
			}
			file << "}\n";
			// FALSE branch
			if (!falseIsEmpty)
			{
				file << "else\n{\n";
				condition_road = TempCond->GetFalseConn()->getDstStat();
				while (!condition_road->IsEnd())
				{
					condition_road->GenerateCode(file);
					condition_road = condition_road->GetOutConnector()->getDstStat();
				}
				file << "}\n";
			}

			if ((condition_road->IsEnd()))
			{
				condition_road->GenerateCode(file);
				break;
			}
		}

		current = (current->GetOutConnector())->getDstStat();
		
	}
	return true;
}

void ApplicationManager::SaveAll(ofstream& file)
{
	file << StatCount << endl;
	for (int i = 0; i < StatCount; i++) {
		StatList[i]->Save(file);
	}
	file << ConnCount << endl;
	for (int i = 0; i < ConnCount; i++) {
		ConnList[i]->Save(file);
	}
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
	if (pClipboard)
	{
		delete pClipboard;
	}
	delete pIn;
	delete pOut;
	
}
