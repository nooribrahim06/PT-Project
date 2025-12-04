#include "Connector.h"

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
	if (Start.x == End.x) // vertical line 
	{
		if (Start.y < End.y)
			return (P.y >= Start.y && P.y <= End.y);
		if (Start.y > End.y)
			return (P.y >= End.y && P.y <= Start.y);
	}
	else if (Start.y == End.y) // horizontal line 
	{
		if (Start.x < End.x)
			return (P.x >= Start.x && P.x <= End.x);
		if (Start.x > End.x)
			return (P.x >= End.x && P.x <= Start.x);
	}
	else 
	{
		if (Start.x < End.x)
		{
			if (P.y == Start.y)
				return (P.x >= Start.x && P.x <= End.x);
			if (P.x == End.x)
				return (P.y >= Start.y && P.y <= End.y);
		}
		if (Start.x > End.x)
		{
			if (P.y == Start.y)
				return (P.x >= End.x && P.x <= Start.x);
			if (P.x == End.x)
				return (P.y >= Start.y && P.y <= End.y);
		}
	}
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
	pOut->DrawConnector(Start, End);
}

