#include "Connector.h"
#include "Statements/Statement.h"
#include <cmath>   // for std::abs
#include <iostream>
#include <fstream>
#include"condition.h"
using namespace std;

Connector::Connector(Statement* Src, Statement* Dst)	
//When a connector is created, it must have a source statement and a destination statement
//There are NO FREE connectors in the flowchart
{
	
	SrcStat = Src;
	DstStat = Dst;
	Selected = false;
}

void Connector::setSrcStat(Statement *Src)
{	SrcStat = Src;	}

Statement* Connector::getSrcStat()
{	return SrcStat;	}

void Connector::setDstStat(Statement *Dst)
{	DstStat = Dst;	}

Statement* Connector::getDstStat()
{	return DstStat;	}


void Connector::setStartPoint(Point P)
{	Start = P;	}

Point Connector::getStartPoint()
{	return Start;	}

bool Connector::IsPointInside(Point P) 
{
	const int tol = 10;  // "thickness" of the clickable area

	// ----- Case 1: pure vertical connector (Start.x == End.x) -----
	if (Start.x == End.x)
	{
		int minY = min(Start.y, End.y);
		int maxY = max(Start.y, End.y);

		bool withinY = (P.y >= minY && P.y <= maxY);
		bool closeX = (std::abs(P.x - Start.x) <= tol);

		return withinY && closeX;
	}

	// ----- Case 2: pure horizontal connector (Start.y == End.y) -----
	if (Start.y == End.y)
	{
		int minX = min(Start.x, End.x);
		int maxX = max(Start.x, End.x);

		bool withinX = (P.x >= minX && P.x <= maxX);
		bool closeY = (std::abs(P.y - Start.y) <= tol);

		return withinX && closeY;
	}

	// ----- Case 3: general L-shaped connector -----
	// Segment 1: horizontal from (Start.x, Start.y) to (End.x, Start.y)
	{
		int minX = min(Start.x, End.x);
		int maxX = max(Start.x, End.x);

		bool withinX = (P.x >= minX && P.x <= maxX);
		bool closeY = (std::abs(P.y - Start.y) <= tol);

		if (withinX && closeY)
			return true;
	}

	// Segment 2: vertical from (End.x, Start.y) to (End.x, End.y)
	{
		int minY = min(Start.y, End.y);
		int maxY = max(Start.y, End.y);

		bool withinY = (P.y >= minY && P.y <= maxY);
		bool closeX = (std::abs(P.x - End.x) <= tol);

		if (withinY && closeX)
			return true;
	}

	return false;
}

bool Connector::IsSelected()
{
	return Selected;
}

void Connector::Setselected(bool S)
{
	Selected = S;
}

void Connector::setEndPoint(Point P)
{	End = P;	}

Point Connector::getEndPoint()
{	return End;	}

void Connector::Draw(Output* pOut) const
{
	///TODO: Call Output to draw a connector from SrcStat to DstStat on the output window
	pOut->DrawConnector(Start, End, Selected);
}

void Connector::Save(ofstream& OutFile) {
	int out = 0;
	if (SrcStat->Isconditional())
	{
		Condition* cond = dynamic_cast<Condition*>(SrcStat);
		if (cond)
		{
			if (this == cond->GetTrueConn())
				out = 1;
			else if (this == cond->GetFalseConn())
				out = 2;
		}
	}
	OutFile << SrcStat->GetstatementID() << "   " << DstStat->GetstatementID() << "   " << out << endl;
}

void Connector::Load(ifstream& InFile, int& srcID, int& dstID, int& type)
{
	InFile >> srcID >> dstID >> type;
	
}

Connector::~Connector()
{
	// IMPORTANT:
	// - Do NOT delete SrcStat or DstStat
	// - Do NOT access *SrcStat or *DstStat here
	// They are owned and deleted by ApplicationManager (StatList),
	// and by the time connectors are being deleted, those statements
	// are already gone.
	SrcStat = nullptr;
	DstStat = nullptr;
}
