#include "Output.h"
#include <iostream>

Output::Output()
{
	//Initialize user interface parameters
	UI.width = 1200;
	UI.height = 620;
	UI.wx = 15;
	UI.wy = 15;

	UI.AppMode = DESIGN;	//Design Mode is the default mode

	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 50;
	UI.DrawingAreaWidth = 0.75 * UI.width;

	UI.DrawColor = BLUE;
	UI.HighlightColor = RED;
	UI.MsgColor = BLACK;

	UI.ASSGN_WDTH = 150;
	UI.ASSGN_HI = 50;

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Programming Techniques Project");

	pWind->SetPen(RED, 3);

	CreateDesignToolBar();
	CreateStatusBar();
	ClearDrawArea();
	ClearOutputBar();
}


Input* Output::CreateInput()
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y)
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar()
{
	pWind->DrawLine(0, UI.height - UI.StatusBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
//TODO: Complete this function
void Output::CreateDesignToolBar() //Draws the Design Menu
{
	UI.AppMode = DESIGN;	//Design Mode
	ClearToolBar();
	//fill the tool bar 

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in Defs.h ==> enum DrawMenuItem

	//commented out to avoid errors

	string MenuItemImages[DSN_ITM_CNT];

	MenuItemImages[ITM_STRAT] = "images\\start.jpg"; // D
	MenuItemImages[ITM_END] = "images\\end.jpg";  // D

	MenuItemImages[ITM_VALUE_ASSIGN] = "images\\assign_val.jpg";
	MenuItemImages[ITM_VAR_ASSIGN] = "images\\assign_var.jpg"; //D
	MenuItemImages[ITM_OPER_ASSIGN] = "images\\assign_operand.jpg"; //D
	MenuItemImages[ITM_COND] = "images\\assign_cond.jpg";

	MenuItemImages[ITM_VAR_DECLARE] = "images\\var_declare.jpg";   // TEMP icon (you don’t have declare.jpg)
	// I can generate a real one if you want // D

	MenuItemImages[ITM_INPUT] = "images\\input.jpg"; // D
	MenuItemImages[ITM_OUTPUT] = "images\\output.jpg"; //D

	MenuItemImages[ITM_CONNECT] = "images\\connector.jpg"; //D
	MenuItemImages[ITM_SELECT] = "images\\select.jpg";
	MenuItemImages[ITM_EDIT] = "images\\edit.jpg";
	MenuItemImages[ITM_DELETE] = "images\\delete.jpg";

	MenuItemImages[ITM_COPY] = "images\\copy.jpg";
	MenuItemImages[ITM_CUT] = "images\\cut.jpg";
	MenuItemImages[ITM_PASTE] = "images\\paste.jpg";

	MenuItemImages[ITM_SAVE] = "images\\Save.jpg";
	MenuItemImages[ITM_LOAD] = "images\\load.jpg";

	//MenuItemImages[ITM_GEN_CODE] = "images\\debug.jpg";    // OR run.jpg if you want a different look
	//// Tell me which file you want for GEN_CODE

	MenuItemImages[ITM_UNDO] = "images\\undo.jpg";
	MenuItemImages[ITM_REDO] = "images\\redo.jpg";

	MenuItemImages[ITM_SIM_MODE] = "images\\sim.jpg";      // simulation mode icon
	MenuItemImages[ITM_EXIT] = "images\\Exit.jpg";

	//TODO: Prepare images for each menu item and add it to the list DONE

	for (int i = 0; i < DSN_ITM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(BLACK, 2);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
void Output::ClearToolBar()
{
	// Clear the whole toolbar area (top strip of the window)
	pWind->SetPen(BLACK, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////
//TODO: Complete this function
void Output::CreateSimulationToolBar() //Draws the Simulation Menu
{
	UI.AppMode = SIMULATION;	//Simulation Mode
	ClearToolBar();
	///TODO: add code to create the simulation tool bar
	string MenuItemImages[SIM_ITM_CNT];
	MenuItemImages[ITM_VALIDATE] = "images\\validate.jpg";          // Validate
	MenuItemImages[ITM_RUN] = "images\\run.jpg";            // Run
	MenuItemImages[ITM_DEBUG] = "images\\debug.jpg";          // Debugging
	MenuItemImages[ITM_GEN_CODE] = "images\\gen_code.jpg";       // Generate code
	MenuItemImages[ITM_DSN_MODE] = "images\\design.jpg";       // Generate code
	MenuItemImages[ITM_EXIT_SIM] = "images\\Exit.jpg";
	//Draw menu item one image at a time
	for (int i = 0; i < SIM_ITM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(BLACK, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearDrawArea()
{
	pWind->SetPen(BLACK, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.DrawingAreaWidth, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearOutputBar()
{
	//Create output bar by drawing a filled rectangle
	pWind->SetPen(BLACK, 2);
	pWind->SetBrush(LIGHTBLUE);
	pWind->DrawRectangle(UI.DrawingAreaWidth, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::PrintMessage(string msg)	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight / 1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(iX, iY, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////

//======================================================================================//
//								Statements Drawing Functions								//
//======================================================================================//

//Draw assignment statement and write the "Text" on it
void Output::DrawAssign(Point Left, int width, int height, string Text, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color

	//Draw the statement block rectangle
	pWind->DrawRectangle(Left.x, Left.y, Left.x + width, Left.y + height);

	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x + width / 6, Left.y + height / 3, Text);
}

//TODO: Add similar functions for drawing all other statements.
//		e.g. DrawDeclareStat(.....), DrawCondtionalStat(......), DrawStart(......), DrawEnd(.......), ...etc
//		Decide the parameters that should be passed to each of them

//TODO: Add DrawConnector function

//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintOnOutputBar(string msg, int L)
{
	int x = UI.DrawingAreaWidth + 10;
	int y = UI.ToolBarHeight + 20 + (L * 20);
	DrawString(x, y, msg);
}

void Output::DrawStart(Point left, int width, int height, string Text, bool Selected)
{
	if (Selected)  // then the pen gonna have highleted color
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3); // normal color 
	// draw the ellipse
	pWind->DrawEllipse(left.x, left.y, left.x + width, left.y + height);

	pWind->SetPen(BLACK, 2);
	pWind->DrawString(left.x + width / 3, left.y + height / 3, Text);
}

//Everywhere: change left.y + height / 4 ? left.y + height / 3.
//Diamond : keep relative offset like center.y - height / 8 for text.

void Output::DrawEnd(Point left, int width, int height, string Text, bool Selected)
{
	if (Selected)  // then the pen gonna have highleted color
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3); // normal color 
	// draw the ellipse
	pWind->DrawEllipse(left.x, left.y, left.x + width, left.y + height);

	pWind->SetPen(BLACK, 2);
	pWind->DrawString(left.x + width / 3, left.y + height / 3, Text);
}

void Output::DrawDeclareStatement(Point left, int width, int height, string Text, bool Selected)
{
	if (Selected)  // then the pen gonna have highleted color
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3); // normal color 
	// draw the rectangle
	pWind->DrawRectangle(left.x, left.y, left.x + width, left.y + height);

	pWind->SetPen(BLACK, 2);
	pWind->DrawString(left.x + width / 5, left.y + height / 3, Text);
}


void Output::DrawInputStatement(Point left, int width, int height, string Text, bool Selected)
{
	if (Selected)  // then the pen gonna have highleted color
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3); // normal color 
	// draw the left trapezoid
	int shift = width / 4; // amount of horizontal shift for bottom points
	int X_points[4] = {
		left.x,                  // P0: top-left
		left.x + width,          // P1: top-right
		left.x + width + shift,  // P2: bottom-right shifted right
		left.x + shift           // P3: bottom-right shifted right
	};

	int Y_points[4] = {
		left.y,              // P0: top edge
		left.y,              // P1: top edge
		left.y + height,     // P2: bottom edge
		left.y + height      // P3: bottom edge
	};
	pWind->DrawPolygon(X_points, Y_points, 4);
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(left.x + width / 3, left.y + height / 3, Text);
}

void Output::DrawOutputStatement(Point left, int width, int height, string Text, bool Selected)
{
	if (Selected)  // then the pen gonna have highleted color
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3); // normal color 
	// draw the right-leaning trapezoid
	int shift = width / 4; // amount of horizontal shift for bottom points
	int X_points[4] = {
		left.x,                  // P0: top-left
		left.x + width,          // P1: top-right
		left.x + width - shift,  // P2: bottom-right shifted left
		left.x - shift           // P3: bottom-left shifted left
	};

	int Y_points[4] = {
		left.y,              // P0: top edge
		left.y,              // P1: top edge
		left.y + height,     // P2: bottom edge
		left.y + height      // P3: bottom edge
	};
	pWind->DrawPolygon(X_points, Y_points, 4);
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(left.x + width / 6, left.y + height / 3, Text);
}

void Output::DrawCondStatement(Point center, int width, int height, string Text, bool Selected)
{
	if (Selected)  // then the pen gonna have highleted color
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3); // normal color 
	// draw the diamond
	int X_points[4] = {
		center.x,                // Top vertex P0
		center.x + (width / 2),  // right vertex P1
		center.x,			     // down vertex P2
		center.x - (width / 2),			     // left vertex P3
	};
	int Y_points[4] = {
		center.y - (height / 2), // Top vertex P0
		center.y,                // right vertex P1
		center.y + (height / 2), // down vertex P2
		center.y                 // left vertex P3
	};
	pWind->DrawPolygon(X_points, Y_points, 4);

	pWind->SetPen(BLACK, 2);
	pWind->DrawString(center.x - (width / 6), center.y - (height / 6), Text);
}

void Output::DrawConnector(Point P1, Point P2, bool Selected)
{
	if (Selected)  // then the pen gonna have highleted color
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3); // normal color 
	// draw line from P1 to mid oy P2
	if (P1.x == P2.x) // vertical line
	{
		pWind->DrawLine(P1.x, P1.y, P2.x, P2.y);
		int L = 8; // length of arrowhead lines
		if (P1.y < P2.y) // arrowhead direction
		{
			L = -L;
		}
		pWind->DrawLine(P2.x, P2.y, P2.x + 6, P2.y + L);
		pWind->DrawLine(P2.x, P2.y, P2.x - 6, P2.y + L);
	}
	else if (P1.y == P2.y) // horizontal line 
	{
		pWind->DrawLine(P1.x, P1.y, P2.x, P2.y);
		int L = 8; // length of arrowhead lines
		if (P1.x < P2.x) // arrowhead direction
		{
			L = -L;
		}
		pWind->DrawLine(P2.x, P2.y, P2.x + L, P2.y - 6);
		pWind->DrawLine(P2.x, P2.y, P2.x + L, P2.y + 6);
	}
	else // general case
	{
		pWind->DrawLine(P1.x, P1.y, P2.x, P1.y);
		pWind->DrawLine(P2.x, P1.y, P2.x, P2.y);
		int L = 8; // length of arrowhead lines
		if (P1.y < P2.y) // arrowhead direction
		{
			L = -L;
		}
		pWind->DrawLine(P2.x, P2.y, P2.x + 6, P2.y + L);
		pWind->DrawLine(P2.x, P2.y, P2.x - 6, P2.y + L);
	}
}

Output::~Output()
{
	delete pWind;
}
