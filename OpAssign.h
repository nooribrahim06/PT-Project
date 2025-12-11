#pragma once
#include "HelperFn.h"
#include "Statements/Statement.h"
class OpAssign :
    public Statement
{
    string LHS; // keep it string right now but it must be variable
    string RHS1;
    string RHS2;
    string op;
    Connector* pOutConn; // must be one connector going to next statement
    Point Inlet; //A point where connections enters this statement 
    Point Outlet;	//A point a connection leaves this statement
    Point LeftCorner;	//left corenr of the statement block.

    virtual void UpdateStatementText();
public:
    OpAssign(Point Lcorner, string L, string R1, string R2, string op);
    void setLHS(const string& L);
    void setRHS(const string& R1, const string R2, const  string OP);
    virtual void Draw(Output* pOut) const;
    void Save(ofstream& OutFile) override;
    void Load(ifstream& InFile) override;
	void Edit(string newLHS, string newRHS, string newRHS2, string newOp);
    Statement* Simulate(Input* pIn, Output* pOut) override;
	Point GetOutletPoint() const override;
	Point GetInletPoint() const override;
    Connector* GetOutConnector() const override;
    virtual void SetOutconnector(Connector* C) override;
	bool IsPointInside(Point P) const override;
	void  GenerateCode(ofstream& OutFile) override;
    //Statement* Clone() const override;
    bool Validate(varinfo vars[], int& varcount, string& msg) override;

};

    

