#include "ApplicationManager.h"

//NOTE: YOU MUST NOT CHANGE THE MAIN FUNCTION

int main()
{
	ActionType ActType;
	//Create an object of ApplicationManager
	ApplicationManager AppManager;
	do
	{		
		//Step I - Read user input (action)
		ActType = AppManager.GetUserAction();

		//Steps II & III - Create & Exexute the action
		AppManager.ExecuteAction(ActType);

		//Step IV - Update the interface
		AppManager.UpdateInterface();	

	} while (ActType != EXIT ); //N: changed to EXIT1	
	return 0;
}

