#pragma once
#include "Statements\Statement.h"
class Declare: public Statement
{
private:
	string var;
    Connector* pOutConn; // must be one connector going to next statement
    Point Inlet; //A point where connections enters this statement 
    Point Outlet;	//A point a connection leaves this statement
    Point LeftCorner;	//left corenr of the statement block.

    virtual void UpdateStatementText();
public:
    Declare(Point Lcorner,string& var);
    virtual void Draw(Output* pOut) const;
    void Save(ofstream& OutFile) override;
    void Load(ifstream& InFile) override;
    void Simulate() override;
	void  GenerateCode(ofstream& OutFile) override;
	bool Validate(varinfo vars[], int& varcount, string& msg) override;
	
};