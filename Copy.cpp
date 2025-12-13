#include "Copy.h"
#include "ApplicationManager.h"
#include "GUI/Output.h"
#include "GUI/Input.h"
#include "Statements/Statement.h" // or "Statements/Statement.h" depending on your tree

Copy::Copy(ApplicationManager* pApp)
    : Action(pApp)
{
}

void Copy::ReadActionParameters()
{
    // Nothing. We rely on previously selected statement.
}

void Copy::Execute()
{
    Output* pOut = pManager->GetOutput();

    // 1) Get the currently selected statement from ApplicationManager
    Statement* sel = pManager->GetSelectedStatement();

    if (!sel)
    {
        pOut->PrintMessage("Error: No statement is selected to copy.");
        return;
    }

    // 2) Clear old clipboard content (avoid leaks)
    pManager->ClearClipboard();   // you already have this function

    // 3) Clone the selected statement (snapshot; no connectors)
    Statement* cloned = sel->Clone();

    // 4) Store the clone in clipboard
    pManager->SetClipboard(cloned);

    // 5) Tell the user it worked
    pOut->PrintMessage("Statement copied to clipboard.");
}
