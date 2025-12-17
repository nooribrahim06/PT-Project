#include "Paste.h"
#include "ApplicationManager.h"
#include "GUI/Output.h"
#include "GUI/Input.h"
Paste::Paste(ApplicationManager * pApp) : Action(pApp)
{
	pCopiedStat = nullptr;
}

void Paste::ReadActionParameters()
{
	// Nothing. We rely on previously copied statement.
}

void Paste::Execute()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    // 1) Check clipboard
    Statement* clip = pManager->GetClipboard();
    if (!clip)
    {
        pOut->PrintMessage("Paste failed: clipboard is empty.");
        return;
    }

    // 2) Ask user where to paste
    Point P;
    pOut->PrintMessage("Paste: Click where you want to paste the statement.");
    while (true)
    {
        pIn->GetPointClicked(P);
        if (pOut->IsInDrawingArea(P))
            break;

        pOut->PrintMessage("Invalid location. Click INSIDE the drawing area.");
    }
    pOut->ClearStatusBar();

    // 3) Clone clipboard snapshot
    Statement* pasted = clip->Clone();    // NO connectors, same data

    // 4) Move pasted statement to user’s chosen position
    pasted->Move(P);

    // 5) Add to the application’s statement list
    pManager->AddStatement(pasted);


    // 6) Optionally select the new pasted statement
    pasted->SetSelected(false);

    // 7) Redraw
    pManager->UpdateInterface();

    pOut->PrintMessage("Statement pasted.");
}