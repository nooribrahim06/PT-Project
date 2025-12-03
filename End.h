#pragma once
#include "statements/Statement.h"
class End :
    public Statement
{
	Point Inlet; //A point where connections enters this statement
	Point Leftcorner; //center point of the End statement
	void UpdateStatementText() override; // to update the statement text (virtual function)   
public:
    End(Point Lcorner);
	virtual void Draw(Output* pOut) const;
    void Save(ofstream& OutFile) override;
    void Load(ifstream& InFile) override;
	void Edit() override;
	Point GetOutletPoint() const override;
	Point GetInletPoint() const override;
    void Simulate() override;
	void  GenerateCode(ofstream& OutFile) override;
	bool IsPointInside(Point P) const override;
	bool IsEnd() const override;
    bool Validate(varinfo vars[], int& varcount, string& msg) override;
};
