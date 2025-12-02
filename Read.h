#pragma once
#include "Statements/Statement.h"
class Read :
    public Statement
{
	string varName;
	Connector* pOutConn; // must be one connector going to next statement
	Point Inlet; //A point where connections enters this statement
	Point Outlet;	//A point a connection leaves this statement
	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

	public:
	Read(Point Lcorner,const string& var);
	virtual void Draw(Output* pOut) const;
	void Save(ofstream& OutFile) override;
	void Load(ifstream& InFile) override;
	void Edit() override;
	void Simulate() override;
	void  GenerateCode (ofstream& OutFile) override;
	//Statement* Clone() const override;
	bool checkvar(varinfo vars[], int& varcount, string& msg) override;

};
