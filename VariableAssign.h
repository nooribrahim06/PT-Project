#pragma once
#include "Statements/Statement.h"
class VariableAssign :
    public Statement
{
private:
    string LHS; // keep it string right now but it must be variable
    string RHS; // must be a varaible (declared)
    Connector* pOutConn; // must be one connector going to next statement
    Point Inlet; //A point where connections enters this statement 
    Point Outlet;	//A point a connection leaves this statement
    Point LeftCorner;	//left corenr of the statement block.

    virtual void UpdateStatementText();

public:
    VariableAssign(Point Lcorner, string left = "", string right = "");

    void setLHS(const string& L);
    void setRHS(const string& R);

    // this is for now 
    // TODO 
    void Draw(Output* pOut) const override;
    void Save(ofstream& OutFile) override;
    void Load(ifstream& InFile) override;
	void Edit() override;
    Statement* Simulate(Input* pIn, Output* pOut) override;
	void  GenerateCode(ofstream& OutFile) override; //n
    Point GetOutletPoint() const override; //n
	Point GetInletPoint() const override; //n
    Connector* GetOutConnector() const override;
    virtual void SetOutconnector(Connector* C) override;
	bool IsPointInside(Point P) const override; //n
	bool Validate(varinfo vars[], int& varcount, string& msg) override;
     // Statement* Clone() const override;
    //Statement* Clone() const override;
    //void SetInlet / SetOutlet(depends on type)
    //    bool IsPointInside(int x, int y);   // for selection

};