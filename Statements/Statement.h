#ifndef STATEMENT_H
#define STATEMENT_H

#include "..\defs.h"
#include "..\Connector.h"
//class Output;
#include "..\GUI\Output.h"



struct varinfo {
	string name;
	bool declared;
	bool initialized;
};
 inline int Findvarindex(const string&name ,varinfo vars[],int varcount) {
	 for (int i = 0; i < varcount; i++) {
		 if (vars[i].name == name) {
			 return i;
		 }
	 }
	 return -1;
 }
//Base class for all Statements
class Statement
{
protected:
	static int ID;			//Each Statement has an ID --> must be unique
	int statementID;   //the ID of this statement
	string Text;	//Statement text (e.g.  "X = 5" OR "salary > 3000" and so on)
	bool Selected;	//true if the statement is selected on the folwchart


	virtual void UpdateStatementText() = 0;	//is called when any part of the stat. is edited	

	/// Add more parameters if needed.

public:
	Statement();

	int GetstatementID() const; // get the current statement ID

	void SetSelected(bool s);
	bool IsSelected() const;

	virtual void Draw(Output* pOut) const  = 0;	//Draw the statement
	virtual void Save(ofstream& OutFile) = 0;
	virtual void Load(ifstream& Infile) = 0;
	virtual void Edit() = 0;
	virtual void Simulate() ;
	virtual void GenerateCode(ofstream& OutFile) = 0;
	/*virtual Statement* Clone() const = 0;*/
	virtual bool IsStart() const;
	virtual bool IsEnd() const;
	virtual bool Isconditional() const;
	virtual bool Validate(varinfo vars[], int &varcount,string &msg) =0;
	virtual Point GetOutletPoint() const = 0;
	virtual Point GetInletPoint() const = 0;
	virtual Connector* GetOutConnector() const = 0;
	virtual void SetOutconnector(Connector* C) = 0;
	virtual bool IsPointInside(Point P) const = 0;
	virtual ~Statement();
	///TODO:The following functions should be supported by the Statement class
	///		It should then be overridden by each derived Statement
	///		Decide the parameters that you should pass to each function and its return type

	//virtual void Save(ofstream &OutFile) = 0;	//Save the Statement parameters to a file
	//virtual void Load(ifstream &Infile) = 0;	//Load the Statement parameters from a file

	//virtual void Edit() = 0;		//Edit the Statement parameter

	//virtual void Simulate();	//Execute the statement in the simulation mode

	//[BONUS] virtual void GenerateCode(ofstream &OutFile) = 0;	//write the statement code to a file


	///TODO: Add more functions if needed

};

#endif