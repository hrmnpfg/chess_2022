#include "square.hpp"
#include "piece.hpp"
#include <string>

using namespace std;

string piece::getName()
{
	string a;
	if(isWhite) a="1";
	else a="0";
	return name + a;
}

bool piece::checkMove(square a, square b)
{
	return false;
}

bool piece::event()
{
	return false;
}

void piece::setEvent()
{
}

king::king(bool w)
{
	hasMoved=false;
	isWhite=w;
	name="K";
}

queen::queen(bool w)
{
	isWhite=w;
	name="Q";
}

knight::knight(bool w)
{
	isWhite=w;
	name="N";
}

bishop::bishop(bool w)
{
	isWhite=w;
	name="B";
}

pawn::pawn(bool w)
{
	bool lastMove;
	isWhite=w;
	name="P";
}

rook::rook(bool w)
{
	hasMoved=false;
	isWhite=w;
	name="R";
}

bool king::checkMove(square a, square b)
{
	if(a.name == b.name) return false;
	int t1=a.name[0]-b.name[0];
	int t2=a.name[1]-b.name[1];
	if(t1==2 && t2==0 && hasMoved==false)
	return true;
	if(t1<=1 && t1>=-1 && t2<=1 && t2>=-1)
	return true;
	return false;
}
bool king::event()
{
	return !hasMoved;
}

void king::setEvent()
{
	hasMoved=true;
}

bool queen::checkMove(square a, square b)
{
	if(a.name == b.name) return false;
	int t1=a.name[0]-b.name[0];
	int t2=a.name[1]-b.name[1];
	if(t1<0) t1=-t1;
	if(t2<0) t2=-t2;
	if(t1==t2 || t1==0 || t2==0) return true;
	return false;
}

bool knight::checkMove(square a, square b)
{
	if(a.name == b.name) return false;
	int t1=a.name[0]-b.name[0];
	int t2=a.name[1]-b.name[1];
	if(t1<0) t1=-t1;
	if(t2<0) t2=-t2;
	if((t1==1 && t2==2) || (t1==2 && t2==1)) return true;
	return false;
}

bool bishop::checkMove(square a, square b)
{
	if(a.name == b.name) return false;
	int t1=a.name[0]-b.name[0];
	int t2=a.name[1]-b.name[1];
	if(t1<0) t1=-t1;
	if(t2<0) t2=-t2;
	if(t1==t2) return true;
	return false;
}

bool pawn::checkMove(square a, square b)
{
	if(a.name == b.name) return false;
	int t1=a.name[0]-b.name[0];
	int t2=a.name[1]-b.name[1];
	if(t2>2) return false;
	if(isWhite==true)
	{
		if(a.name[1]=='2' && b.name[1]=='4' && t1==0)
		return true;
		if(t2==-1 && t1<2 && t1>-2)
		return true;
	}
	else
	{
		if(a.name[1]=='7' && b.name[1]=='5' && t1==0)
		return true;
		if(t2==1 && t1<2 && t1>-2)
		return true;
	}
	return false;
}

bool pawn::event()
{
	return lastMove;
}

void pawn::setEvent()
{
	lastMove=true;
}

bool rook::checkMove(square a, square b)
{
	if(a.name == b.name) return false;
	int t1=a.name[0]-b.name[0];
	int t2=a.name[1]-b.name[1];
	if(t1==0 || t2==0)
	return true;
	return false;
}

bool rook::event()
{
	return !hasMoved;
}
void rook::setEvent()
{
	hasMoved=true;
}
