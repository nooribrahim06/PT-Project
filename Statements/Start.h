#pragma once
#include "Statement.h"
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
	Statement* Simulate(Input* pIn, Output* pOut) override;
	void  GenerateCode(ofstream& OutFile) override;
	Point GetOutletPoint() const override;
	Point GetInletPoint() const override;
	Connector* GetOutConnector() const override;
	virtual void SetOutconnector(Connector* C) override;
	bool IsStart() const override;
	bool IsPointInside(Point P) const override;
	virtual void Move(const Point& P) override;
	virtual Statement* Clone() const override;
	bool Validate(varinfo vars[], int& varcount, string& msg) override;
};