#ifndef SQUARE_HPP
#define SQUARE_HPP
#include <iostream>
#include "piece.hpp"
#include <string>

class piece;

class square
{
private:
	piece *contents;
	
public:
	std::string name;
	
	square(std::string s);
	
	void placePiece(std::string name, bool w);
	void removePiece();
	bool makeMove(square s);
	void move(square* s);
	std::string getContents();
	bool specialEvent();
	void setEvent();
};

#endif
