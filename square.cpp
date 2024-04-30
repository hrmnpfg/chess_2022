#include "square.hpp"
#include "piece.hpp"
#include <string>
#include <cstdlib>

using namespace std;

string square::getContents()
{
	if(contents==nullptr) return "  ";
	return contents->getName();
}

square::square(std::string s)
{
	contents=nullptr;
	name=s;
}

void square::placePiece(string name, bool w)
{
	if(name=="king")
	{
		this->removePiece();
		contents=new king(w);
		return;
	}
	if(name=="queen")
	{
		this->removePiece();
		contents=new queen(w);
		return;
	}
	if(name=="knight")
	{
		this->removePiece();
		contents=new knight(w);
		return;
	}
	if(name=="bishop")
	{
		this->removePiece();
		contents=new bishop(w);
		return;
	}
	if(name=="pawn")
	{
		this->removePiece();
		contents=new pawn(w);
		return;
	}
	if(name=="rook")
	{
		this->removePiece();
		contents=new rook(w);
		return;
	}
}

void square::removePiece()
{
	if(contents!=nullptr) delete contents;
	contents=nullptr;
}

bool square::makeMove(square s)
{
	return contents->checkMove(*this,s);
}

void square::move(square* s)
{
	int mate=0;
	if(s->contents!=nullptr)
	{
		if(s->getContents()[0]=='K')
		{
			if(s->getContents()[1]=='1') mate=1;
			else mate=-1;
		}
	}
	bool w=false;
	if(this->getContents()[1]=='1') w=true;
	string name=this->getContents();
	s->removePiece();
	
	if(name[0]=='N')
	{
		s->placePiece("knight",w);
	}
	if(name[0]=='B')
	{
		s->placePiece("bishop",w);
	}
	if(name[0]=='Q')
	{
		s->placePiece("queen",w);
	}
	if(name[0]=='R')
	{
		s->placePiece("rook",w);
		s->setEvent();
	}
	if(name[0]=='K')
	{
		s->placePiece("king",w);
		s->setEvent();
	}
	if(name[0]=='P')
	{
		if(s->name[1]-name[1]==2 || s->name[1]-name[1]==-2)
		{
			s->placePiece("pawn",w);
			s->setEvent();
		}
		else if(s->name[1]=='8'||s->name[1]=='1')
		{
			s->placePiece("queen",w);
		}
		else s->placePiece("pawn",w);
	}
	this->removePiece();
	if(mate==1) throw (1);
	if(mate==-1) throw (-1);
}

bool square::specialEvent()
{
	if(contents!=nullptr)
	{
		if(contents->getName()[0]=='K') return contents->event();
		if(contents->getName()[0]=='R') return contents->event();
		if(contents->getName()[0]=='P') return contents->event();
	}
	return false;
}

void square::setEvent()
{
	if(contents!=nullptr)
	{
		if(contents->getName()[0]=='K') contents->setEvent();
		if(contents->getName()[0]=='R') contents->setEvent();
		if(contents->getName()[0]=='P') contents->setEvent();
	}
}
