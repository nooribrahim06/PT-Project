#pragma once
#include "Statement.h"
class Condition :
    public Statement
{
    string RHS;
	string LHS;
	string  CompOp;
	Point Inlet; //A point where connections enters this statement
	Point TrueOutlet;	//A point a connection leaves this statement for true case
	Point FalseOutlet;	//A point a connection leaves this statement for false case
	virtual void UpdateStatementText();
	Connector* pTrueOutConn; // true connector
    Connector* pFalseOutConn; // false connector
	Point Center;	//Center of the statement block
	public:
		bool LoopOnTrue;
		bool LoopOnFalse;
	Condition(Point Lcorner, string L="",string Op = "", string R = "");
	void setLHS(const string& L);
	void setRHS(const string& R);
	void setCompOp(const string& Op);
	Connector* GetTrueConn() const;
	void SetTrueConn(Connector* C);
	Connector* GetFalseConn() const;
	void SetFalseConn(Connector* C);
	virtual void Draw(Output* pOut) const;
	void Save(ofstream& OutFile) override;
	void Load(ifstream& InFile) override;
	bool Isconditional() const override;
	bool Validate(varinfo vars[], int& varcount, string& msg) override;
	void Edit(const string& LHS, const string& RHS, const string& CompOp);
	Statement* Simulate(Input* pIn, Output* pOut) override;
	void  GenerateCode(ofstream& OutFile) override;
	void GenerateLoopCode(ofstream& file, bool branch);
	Point GetOutletPoint() const override;
	Point GetTrueOutlet() const;
	Point GetFalseOutlet() const;
	Point GetInletPoint() const override;
	Connector* GetOutConnector() const override;
	virtual void SetOutconnector(Connector* C) override;
	bool IsPointInside(Point P) const override;
	virtual void Move(const Point& P) override;
	virtual Statement* Clone() const override;
};

