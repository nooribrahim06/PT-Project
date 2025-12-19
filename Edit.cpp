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
    : Action(pApp), pStat(nullptr) {}

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

    // ===================== ValueAssign =====================
    if (ValueAssign* pAssign = dynamic_cast<ValueAssign*>(pStat))
    {
        string newLHS, newRHS;

        // LHS must be a variable
        do
        {
            pOut->PrintMessage("Edit: Enter the new variable name (LHS).");
            newLHS = pIn->GetString(pOut);
        } while (!IsVariable(newLHS));

        // RHS must be a value
        do
        {
            pOut->PrintMessage("Edit: Enter the new value (RHS).");
            newRHS = pIn->GetString(pOut);
        } while (!IsValue(newRHS));

        pAssign->Edit(newLHS, newRHS);
    }

    // ===================== VariableAssign =====================
    else if (VariableAssign* pVarAssign = dynamic_cast<VariableAssign*>(pStat))
    {
        string LHS, RHS;

        // LHS must be variable
        do
        {
            pOut->PrintMessage("Edit: Enter a new valid variable name to assign to (LHS).");
            LHS = pIn->GetString(pOut);
        } while (!IsVariable(LHS));

        // RHS must be variable
        do
        {
            pOut->PrintMessage("Edit: Enter a new valid variable name to assign to (RHS).");
            RHS = pIn->GetString(pOut);
        } while (!IsVariable(RHS));

        pVarAssign->Edit(LHS, RHS);
    }

    // ===================== OpAssign =====================
    else if (OpAssign* pOpAssign = dynamic_cast<OpAssign*>(pStat))
    {
        string newLHS, newRHS1, newRHS2, newOp;

        // LHS must be variable
        do
        {
            pOut->PrintMessage("Edit: Enter the new left-hand side variable name (LHS).");
            newLHS = pIn->GetString(pOut);
        } while (!IsVariable(newLHS));

        // RHS1: variable or value
        do
        {
            pOut->PrintMessage("Edit: Enter the first right-hand side operand (var or value).");
            newRHS1 = pIn->GetString(pOut);
        } while (!IsVariable(newRHS1) && !IsValue(newRHS1));

        // Operator: +, -, * or /
        do
        {
            pOut->PrintMessage("Edit: Enter the operator (+, -, *, /).");
            newOp = pIn->GetString(pOut);
        } while (!(newOp == "+" || newOp == "-" || newOp == "*" || newOp == "/"));

        // RHS2: variable or value
        do
        {
            pOut->PrintMessage("Edit: Enter the second right-hand side operand (var or value).");
            newRHS2 = pIn->GetString(pOut);
        } while (!IsVariable(newRHS2) && !IsValue(newRHS2));
        pOpAssign->Edit(newLHS, newRHS1, newRHS2, newOp);
    }

    // ===================== Condition =====================
    else if (Condition* pCond = dynamic_cast<Condition*>(pStat))
    {
        string newLHS;
        string newRHS;
        string newOp;

        // LHS: variable or value
        do
        {
            pOut->PrintMessage("Edit: Enter the new left-hand side (var or value).");
            newLHS = pIn->GetString(pOut);
        } while (!IsVariable(newLHS) && !IsValue(newLHS));

        // Comparator: use your helper
        do
        {
            pOut->PrintMessage("Edit: Enter the comparison operator (==, !=, <, <=, >, >=).");
            newOp = pIn->GetString(pOut);
        } while (!IsValidComparator(newOp));
        // RHS: variable or value
        do
        {
            pOut->PrintMessage("Edit: Enter the new right-hand side (var or value).");
            newRHS = pIn->GetString(pOut);
        } while (!IsVariable(newRHS) && !IsValue(newRHS));

        pCond->Edit(newLHS, newRHS, newOp);
    }

    // ===================== Read =====================
    else if (Read* pRead = dynamic_cast<Read*>(pStat))
    {
        string newVar;

        // Read must take a variable
        do
        {
            pOut->PrintMessage("Edit: Enter the new variable name to read.");
            newVar = pIn->GetString(pOut);
        } while (!IsVariable(newVar));

        pRead->Edit(newVar);
    }

    // ===================== Write =====================
    else if (Write* pWrite = dynamic_cast<Write*>(pStat))
    {
        string newExpr;

        do {
            pOut->PrintMessage("Edit: Enter a variable name, a numeric value, or a message in quotes \"...\".");
            newExpr = pIn->GetString(pOut);

            if (newExpr.empty())
                continue;

            bool isQuoted = (newExpr.front() == '"' && newExpr.back() == '"');
            bool isValue = IsValue(newExpr);
            bool isVariable = IsVariable(newExpr);

            // accept any valid input
            if (isQuoted || isValue || isVariable)
                break;

        } while (true);
        pWrite->Edit(newExpr);
    }

    // ===================== Declare =====================
    else if (Declare* pDec = dynamic_cast<Declare*>(pStat))
    {
        string newVar;

        // Declared name must be a valid variable
        do
        {
            pOut->PrintMessage("Edit: Enter the new variable name to declare.");
            newVar = pIn->GetString(pOut);
        } while (!IsVariable(newVar));

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

