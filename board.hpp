#ifndef BOARD_HPP
#define BOARD_HPP
#include <string>

class piece;
class square;

class board
{
private:
	square* tab[8][8];
	bool turn;
	
	bool makeMove(square a, square b);
	bool checkKnight(char t, int i, int j);
public:
	int checkMate;
	
	board();
	~board();
	
	bool move(std::string s);
	bool checkAttacked(square *s);
	std::string getState();
	void show();
};

#endif
