#ifndef STATEMENT_H
#define STATEMENT_H

#include "..\defs.h"
#include "..\Connector.h"
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

	static const int Maxrunvars = 200;// max no. of run-time variables
	virtual void UpdateStatementText() = 0;	//is called when any part of the stat. is edited	

private:
	static string R_names[Maxrunvars];
	static double R_values[Maxrunvars];
	static int R_count;
	


public:
	static string GetDebug_RunVars();
	static void Resetrunvars();
	static void SetVar(const string& name, double value);
	 static double GetVar(const string& name);
	 

	Statement();

	int GetstatementID() const; // get the current statement ID

	void SetSelected(bool s);
	bool IsSelected() const;

	virtual void Draw(Output* pOut) const  = 0;	//Draw the statement
	virtual void Save(ofstream& OutFile) = 0;
	virtual void Load(ifstream& Infile) = 0;
	virtual Statement* Simulate(Input*pIn,Output*pOut)=0;
	virtual  void GenerateCode(ofstream& OutFile) = 0;
	virtual Statement* Clone() const = 0;
	virtual bool IsStart() const;
	virtual bool IsEnd() const;
	virtual bool Isconditional() const;
	virtual bool Validate(varinfo vars[], int& varcount, string& msg) = 0;
	virtual Point GetOutletPoint() const = 0;
	virtual Point GetInletPoint() const = 0;
	virtual Connector* GetOutConnector() const = 0;
	virtual void SetOutconnector(Connector* C) = 0;
	virtual bool IsPointInside(Point P) const = 0;
	virtual void Move(const Point& P) = 0;
	virtual ~Statement();


};
#endif



