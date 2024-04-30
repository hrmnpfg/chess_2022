#ifndef PIECE_HPP
#define PIECE_HPP
#include <iostream>
#include "square.hpp"
#include <string>

class square;

class piece
{
protected:
	std::string name;
public:
	bool isWhite;
	virtual bool checkMove(square a, square b);
	std::string getName();
	virtual bool event();
	virtual void setEvent();
};

class king : public piece
{
private:
	bool hasMoved;
public:
	king(bool w);
	bool checkMove(square a, square b);
	bool event();
	void setEvent();
};

class queen : public piece
{
public:
	queen(bool w);
	bool checkMove(square a, square b);
};

class knight : public piece
{
public:
	knight(bool w);
	bool checkMove(square a, square b);
};

class bishop : public piece
{
public:
	bishop(bool w);
	bool checkMove(square a, square b);
};

class pawn : public piece
{
private:
	bool lastMove;
public:
	pawn(bool w);
	bool checkMove(square a, square b);
	bool event();
	void setEvent();
};

class rook : public piece
{
private:
	bool hasMoved;
public:
	rook(bool w);
	bool checkMove(square a, square b);
	bool event();
	void setEvent();
};
#endif
