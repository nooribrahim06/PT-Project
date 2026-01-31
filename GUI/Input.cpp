
#include "Input.h"
#include "Output.h"

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(Point& P) const
{
	pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}

string Input::GetString(Output* pO) const
{
	string Label;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if ((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}


double Input::GetValue(Output* pO) const	// Reads a double value from the user 
{
	///TODO: add code to read a double value from the user and assign it to D

	string str = GetString(pO);

	//This function should make any needed validations on the entered text 
	// to make sure it is a double value (e.g. 12.5, -12.5, -23, -23., -23.0 …etc.).

	while (!IsValue(str))
	{
		pO->PrintMessage("Invalid value, please enter a valid double value:");
		str = GetString(pO);
	}

	//Read a double value from the user then return it
	double D = stod(str);
	return D;
}


//TODO: Add the function Input::GetVariable 
// to read a “variable name” from the user (from the keyboard). 
// It does not return before taking a valid variable name.

string Input::GetVariable(Output* pO) const
{
	string varName;
	pO->PrintMessage("Please enter a variable name:");
	varName = GetString(pO);
	//Validate the variable name

	//keep asking till Valid variable name is entered.
	while (!IsVariable(varName))
	{
		pO->PrintMessage("Invalid variable name! Use letters/digits, start with a letter:");
		varName = GetString(pO);
	}

	return varName;

}

//TODO: Add the function Input::GetArithOperator 
// to read an arithmetic operator (+, -, * or /) from the user. 
// It does not return before taking a valid arithmetic operator.

//n: Replace the implementation of GetArithOperator to match the header (return type: string)
string Input::GetArithOperator(Output* pO) const
{
	string opStr;

	pO->PrintMessage("Enter arithmetic operator (+, -, * or /):");
	opStr = GetString(pO);

	while (opStr.size() != 1 ||
		(opStr[0] != '+' && opStr[0] != '-' &&
			opStr[0] != '*' && opStr[0] != '/'))
	{
		pO->PrintMessage("Invalid operator! Please enter one of (+, -, * or /):");
		opStr = GetString(pO);
	}

	return opStr;
}

//TODO: Add the function Input::GetCompOperator
// similar to the previous function but for comparison operators (==, !=, <, <=, > or >=).

string Input::GetCompOperator(Output* pO) const
{
	string op;
	pO->PrintMessage("Enter comparison operator (==, !=, <, <=, > or >=):");
	op = GetString(pO);
	while (op != "==" && op != "!=" && op != "<" && op != "<=" && op != ">" && op != ">=")
	{
		pO->PrintMessage("Invalid operator! Please enter one of (==, !=, <, <=, > or >=):");
		op = GetString(pO);
	}

	return op;
}

//TODO: Complete the implementation of the following function

ActionType Input::GetUserAction() const
{
	//This function reads the position where the user clicks to determine the desired action

	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	// DESIGN MODE

	if (UI.AppMode == DESIGN)	//application is in design mode
	{
		//[1] User clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			// Menu items are lined horizontally
			int ClickedItem = (x / UI.MenuItemWidth);

			switch (ClickedItem)
			{
				//---------------- FLOW / STATEMENTS ----------------
			case ITM_STRAT:        return ADD_START;          // Start statement
			case ITM_END:          return ADD_END;            // End statement

				//---------------- ASSIGNMENTS ----------------------
			case ITM_VALUE_ASSIGN: return ADD_VALUE_ASSIGN;   // simple assignment
			case ITM_VAR_ASSIGN:   return ADD_VAR_ASSIGN;     // variable assignment
			case ITM_OPER_ASSIGN:  return ADD_OPER_ASSIGN;    // operator assignment
			case ITM_COND:         return ADD_CONDITION;      // conditional
			case ITM_VAR_DECLARE:  return ADD_DECLARE_VARIABLE;    // declaration

				//---------------- INPUT / OUTPUT -------------------
			case ITM_INPUT:        return ADD_READ;          // input statement
			case ITM_OUTPUT:       return ADD_WRITE;         // output statement

				//---------------- CONNECTORS -----------------------
			case ITM_CONNECT:      return ADD_CONNECTOR;      // connector

				//---------------- EDIT OPERATIONS ------------------
			case ITM_SELECT:       return SELECT;        // select statement
			case ITM_EDIT:         return EDIT_STAT;          // edit selected
			case ITM_DELETE:       return DEL;                // delete selected

				//---------------- CLIPBOARD OPS --------------------
			case ITM_COPY:         return COPY;               // copy
			case ITM_CUT:          return CUT;                // cut
			case ITM_PASTE:        return PASTE;              // paste

				//---------------- FILE OPS -------------------------
			case ITM_SAVE:         return SAVE;               // save graph to file
			case ITM_LOAD:         return LOAD;               // load graph from file

				//---------------- UNDO / REDO ----------------------
			case ITM_UNDO:         return UNDO;               // undo last action
			case ITM_REDO:         return REDO;               // redo last undone action

				//---------------- MODE SWITCH / EXIT ---------------
			case ITM_SIM_MODE:     return SWITCH_SIM_MODE;    // <== use your actual ActionType for "go to simulation"
			case ITM_EXIT:         return EXIT;               // exit application

			default:               return DSN_TOOL;           // click beyond existing icons
			}
		}

		//[2] User clicks on the drawing or output area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			if (x <= UI.DrawingAreaWidth)
				return DRAWING_AREA;	// user clicked drawing area
			else
				return OUTPUT_AREA;   // user clicked to the right (output / side area)
		}

		//[3] User clicks on the status bar
		return STATUS;
	}

	// SIMULATION MODE

	else	//Application is in Simulation mode
	{
		//[1] User clicks on the Simulation Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItem = (x / UI.MenuItemWidth);

			switch (ClickedItem)
			{
			case ITM_VALIDATE:  return VALIDATE;        // validate the flowchart
			case ITM_RUN:       return RUN;             // run normally
			case ITM_DEBUG:     return DEBUG_RUN;       // step-by-step debug (use your ActionType name)
			case ITM_GEN_CODE:  return GENERATE_CODE;   // generate C++ code to file
			case ITM_DSN_MODE:  return SWITCH_DSN_MODE; // back to design mode
			case ITM_EXIT_SIM:         return EXIT;
			default:            return SIM_TOOL;        // generic "clicked in sim toolbar" if you have such an ActionType
			}
		}

		//[2] User clicks on the drawing or output area (during simulation)
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			// Most templates just treat this as "click in area" without a special action
			// You can reuse DRAWING_AREA / OUTPUT_AREA if you want to inspect clicks in sim.
			if (x <= UI.DrawingAreaWidth)
				return DRAWING_AREA;
			else
				return OUTPUT_AREA;
		}

		//[3] User clicks on the status bar in simulation
		return STATUS;
	}
}


Input::~Input()
{
}

