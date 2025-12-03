#pragma once
#include "Statements/Statement.h"
class Start :
    public Statement
{
	Connector* pOutConn; // must be one connector going to next statement
	Point Outlet;	//A point a connection leaves this statement
	Point LeftCorner;	//left corenr of the statement block.
	void UpdateStatementText() override; // to update the statement text (virtual function)
    public:
    Start(Point Lcorner);
	virtual void Draw(Output* pOut) const;
	void Save(ofstream& OutFile) override;
	void Load(ifstream& InFile) override;
	void Edit() override;
	void Simulate() override;
	void  GenerateCode(ofstream& OutFile) override;
	bool IsStart() const override;
	bool Validate(varinfo vars[], int& varcount, string& msg) override;
};
