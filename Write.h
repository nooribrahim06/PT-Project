#pragma once
#include "Statements/Statement.h"
class Write :
    public Statement
{
    private:
    string var; // variable to write
    Connector* pOutConn; // must be one connector going to next statement
    Point Inlet; //A point where connections enters this statement 
    Point Outlet;	//A point a connection leaves this statement
    Point LeftCorner;	//left corenr of the statement block.
	virtual void UpdateStatementText();
    public:
    Write(Point Lcorner,string& variable);
    virtual void Draw(Output* pOut) const;
    void Save(ofstream& OutFile) override;
    void Load(ifstream& InFile) override;
	void Edit() override;
   Statement* Simulate(Input* pIn, Output* pOut) override;
	Point GetOutletPoint() const override;
    Point GetInletPoint() const override;
    Connector* GetOutConnector() const override;
    virtual void SetOutconnector(Connector* C) override;
	bool IsPointInside(Point P) const override;
	void  GenerateCode(ofstream& OutFile) override;
	bool Validate(varinfo vars[], int& varcount, string& msg) override;
     
};
