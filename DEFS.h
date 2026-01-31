#ifndef DEFS_H
#define DEFS_H

//This file contains some global constants and definitions to be used in the project.

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION
};

// TODO: Add any action type here
enum ActionType // The actions supported
{
	ADD_START, //Add start statement
	ADD_END,   //Add end statement
	ADD_DECLARE_VARIABLE, // Add  declare variable statement
	ADD_VALUE_ASSIGN, //Add value assignment statement
	ADD_VAR_ASSIGN,	  //Add variable assignment statement
	ADD_OPER_ASSIGN,  //Add operator assignment statement
	ADD_CONDITION,    //Add a conditional statement (for if and while-loop statements)
	ADD_READ,  //Add read statement
	ADD_WRITE, //Addd write statemetn

	ADD_CONNECTOR, //Add a connector between two statements

	SELECT,		//Select a statement, a connector
	EDIT_STAT,	//Edit a statement

	DEL,   //Delete a figure
	COPY,  //Copy a figure
	CUT,   //Cut a figure
	PASTE, //Paste a figure

	SAVE,		//Save the whole graph to a file
	LOAD,		//Load a graph from a file

	UNDO,       //n:Undo last action
	REDO,       //n:redo last action
	VALIDATE,   //n:Validate the flowchart
	RUN,        //n:Run the flowchart
	DEBUG_RUN,  //n:Debug the flowchart
	GENERATE_CODE, //n:Generate the code of the flowchart

	SWITCH_DSN_MODE,	//Switch to Design mode
	SWITCH_SIM_MODE,	//Switch to simulatiom mode

	EXIT,		//Exit the application

	//TODO: ADD THE ACTIONS OF SIMULATION MODE


	DRAWING_AREA,  //A click on the drawing area
	OUTPUT_AREA,   //A click on the output area
	DSN_TOOL,	   //A click on an empty place in the design tool bar
	STATUS,		   //A click on the status bar

	SIM_TOOL   //A click on an empty place in the simulation tool bar	
};

// TODO: you should add more items
enum DesignMenuItem //The items of the design menu --> THE ORDER MATTERS
{
	//Note: Items are ordered here as they appear in menu
	//If you change the menu items order, change the order here too
	ITM_STRAT,			//n:Start statement
	ITM_END,			//n:End statement
	ITM_VALUE_ASSIGN,	//simple assignment statement
	ITM_VAR_ASSIGN,		//n:Variable assignment statement--> Age = K
	ITM_OPER_ASSIGN,	//n:Operator assignment statement--> K = A + B or k = 2 * 3
	ITM_COND,			//conditional statement
	ITM_VAR_DECLARE,	//n:Variable declaration statement

	ITM_INPUT,			//n:Input statement
	ITM_OUTPUT,			//n:Output statement

	ITM_CONNECT,		//n:Connector
	ITM_SELECT,			//n:Select statement - i see there is no need to unselect item
	ITM_EDIT,			//n:Edit statement"SELECTED_STAT"
	ITM_DELETE,			//n:Delete statement
	ITM_COPY,			//n:Copy statement
	ITM_CUT,			//n:Cut statement
	ITM_PASTE,			//n:Paste statement
	ITM_SAVE,			//n:Save the whole graph to a file
	ITM_LOAD,			//n:Load a graph from a file

	ITM_UNDO,        //N:Undo last action
	ITM_REDO,        //N:redo last action

	ITM_SIM_MODE,		//n:Switch to Simulation mode
	ITM_EXIT,			//Exit

	//TODO: Add more items names here

	DSN_ITM_CNT		//no. of design menu items ==> This should be the last line in this enum

};

// TODO: you should add more items if needed
enum SimMenuItem //The items of the simulation menu
{
	//Note: Items are ordered here as they appear in menu
	ITM_VALIDATE,	//Validate
	ITM_RUN,	    //Run
	ITM_DEBUG,      //n:Debugging statement
	ITM_GEN_CODE,   //n:Generate code statement
	//TODO:Add more items names here
	ITM_DSN_MODE,
	ITM_EXIT_SIM,	//Switch to Design mode
	SIM_ITM_CNT		//no. of simulation menu items ==> This should be the last line in this enum

};




#ifndef NULL
#define NULL 0
#endif

#endif