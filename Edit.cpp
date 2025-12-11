#include "Edit.h"
#include "ApplicationManager.h"
#include "Statements/Statement.h"
#include "Statements/ValueAssign.h"
#include "OpAssign.h"
#include "Condition.h"
#include "Read.h"
#include "Write.h"
#include "VariableAssign.h"
#include "Declare.h"

#include "Connector.h"
#include "GUI/Input.h"
#include "GUI/Output.h"

// Constructor: just store the manager pointer in the base Action
Edit::Edit(ApplicationManager* pApp) 
    : Action(pApp), pStat(nullptr)
{
}

void Edit::ReadActionParameters()
{
    // We only need the new text from the user.
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pStat = nullptr;

    Connector* selConn = pManager->GetSelectedConn();
    if(selConn)
    {
        pOut->PrintMessage("Error: cannot edit a connector, please select a statement. ");
        return;
    }


    pStat = pManager->GetSelectedStatement();
    if(!pStat)
    {
        pOut->PrintMessage("Error: no statement is selected.");
        return;
    }
    pOut->PrintMessage("Edit: Edit the selected statement.");
   
}

void Edit::Execute()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    ReadActionParameters();

    if (!pStat)
		return;
	if (pStat->IsEnd() || pStat->IsStart())
    {
		pOut->PrintMessage("Error: Start/End statements cannot be edited.");
        return;
    }

    //ValueAssign* pAssign = dynamic_cast<ValueAssign*>(pStat);
    if (ValueAssign* pAssign = dynamic_cast<ValueAssign*>(pStat)) //done
    {
		pOut->PrintMessage("Edit: Enter the new variable name.");
        string newLHS = pIn->GetString(pOut);
        pOut->PrintMessage("Edit: Enter the new value.");
        string newRHS = pIn->GetString(pOut);
        

        pAssign->Edit(newLHS, newRHS);
    }
    else if (VariableAssign* pVarAssign = dynamic_cast<VariableAssign*>(pStat)) //done
    {
        pOut->PrintMessage("Edit: Enter the new variable name.");
        string LHS = pIn->GetString(pOut);
        pOut->PrintMessage("Edit: Enter the new value.");
        string RHS = pIn->GetString(pOut);
        pVarAssign->Edit(LHS, RHS);
    }
	else if (OpAssign* pOpAssign = dynamic_cast<OpAssign*>(pStat)) //done
    {
        pOut->PrintMessage("Edit: Enter the new left-hand side variable name.");
        string newLHS = pIn->GetString(pOut);
        pOut->PrintMessage("Edit: Enter the new right-hand side variable name.");
        string newRHS = pIn->GetString(pOut);
        pOut->PrintMessage("Edit: Enter the new right-hand side 2 variable name.");
        string newRHS2 = pIn->GetString(pOut);
        pOut->PrintMessage("Edit: Enter the new operator.");
        string newOp = pIn->GetString(pOut);

        pOpAssign->Edit(newLHS, newRHS, newRHS2, newOp);
    }
	else if (Condition* pCond = dynamic_cast<Condition*>(pStat)) //done
    {
        pOut->PrintMessage("Edit: Enter the new left-hand side variable name.");
        string newLHS = pIn->GetString(pOut);
        pOut->PrintMessage("Edit: Enter the new right-hand side variable name.");
        string newRHS = pIn->GetString(pOut);
        pOut->PrintMessage("Edit: Enter the new condition operator.");
        string newOp = pIn->GetString(pOut);

        pCond->Edit(newLHS, newRHS, newOp);
    }
	else if (Read* pRead = dynamic_cast<Read*>(pStat)) //done
    {
        pOut->PrintMessage("Edit: Enter the new variable name to read.");
        string newVar = pIn->GetString(pOut);
        pRead->Edit(newVar);
	}
    else if (Write* pWrite = dynamic_cast<Write*>(pStat)) //done
    {
        pOut->PrintMessage("Edit: Enter the new variable name to write.");
        string newVar = pIn->GetString(pOut);
        pWrite->Edit(newVar);
    }
    else if (Declare* pDec = dynamic_cast<Declare*>(pStat))
    {
        pOut->PrintMessage("Edit: Enter the new variable name to declare.");
        string newVar = pIn->GetString(pOut);
        pDec->Edit(newVar);
    }
    else
    {
        pOut->PrintMessage("Error: This statement type cannot be edited.");
        return;
	}


    pManager->UpdateInterface();
    pManager->GetOutput()->ClearStatusBar();


}


