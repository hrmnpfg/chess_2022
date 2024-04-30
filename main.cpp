#include <ncurses.h>
#include "piece.hpp"
#include "square.hpp"
#include "board.hpp"
#include "history.hpp"
#include <cstring>

using namespace std;

void fillBoard(WINDOW *win, board &b, int height, int width, bool rotate);


void my_getline(string& str, WINDOW *wkom)
{
	char ch;
	str.clear();
	while(true)
	{
    	ch=wgetch(wkom);
    	if(ch=='\n') break;
    	str.push_back(ch);
  	}
}


int main(int argc, char *argv[])
{
	WINDOW *my_win;
	int startx, starty, width, height;
	int ch;

	initscr();
	cbreak();
	printw("chess in terminal:");
	move(1,0);
	printw("this is a 2 player game");
	move(2,0);
	printw("to start, press any button");
	refresh();
	
	string name="save.txt";
	if(argc>1) name=argv[1];
	history save(name);
	board game;
	bool p1=true;
	int iter=0;
	while(save.getLast(iter)!="") iter++;
	for(int i=iter-1;i>=0;i--)
	{
		if(game.move(save.getLast(i))) p1=!p1;
	}
	
	string userinput;
	
	WINDOW *mboard;
	int mbw, mbh;
	WINDOW *moves;
	int mow, moh;
	WINDOW *input;
	int ipw, iph;
	WINDOW *instr;
	int isw, ish;
	
	while((ch=getch()) != '\e')
	{
		if(LINES<15 || COLS < 34)
		{
			clear();
			move(0,0);
			printw("window too small");
			move(1,0);
			printw("width: %d height: %d",COLS,LINES);
			refresh();
			ch = getch();
			continue;
		}
		
		if(COLS<48)
		{
			mbw = 34;
			mow = COLS - mbw;
		}
		else if(COLS<84)
		{
			mow = 14;
			mbw = COLS - mow;
		}
		else
		{
			mbw = COLS*5/6+1;
			mow = COLS - mbw;
		}
		ipw = COLS;
		isw = COLS;
		if(LINES<20)
		{
			mbh = 10;
			moh = mbh;
		}
		else
		{
			mbh = LINES-6;
			moh = mbh;	
		}
		iph = 3;
		ish = 3;
		clear();
		mboard = newwin(mbh,mbw,0,0);
		moves = newwin(moh,mow,0,mbw);
		input = newwin(iph,ipw,mbh,0);
		instr = newwin(ish,isw,mbh+iph,0);
		
		
		box(mboard,0,0);
		box(moves,0,0);
		box(input,0,0);
		refresh();
		
		fillBoard(mboard,game,mbh,mbw,p1);
		string move;
		mvwprintw(moves,1,1,"moves");
		if(mow < 14)
		{
			for(int i=0; i<moh-4;i++)
			{
				move=save.getLast(i);
				mvwprintw(moves,i+2,1,move.c_str());
				
			}
		}
		else
		{
			for(int i=0; i<moh-4;i=i+2)
			{
				move=save.getLast(i);
				mvwprintw(moves,i+2,1,move.c_str());
				move=save.getLast(i+1);
				mvwprintw(moves,i+2,8,move.c_str());
			}
		}
		mvwprintw(input,1,1,"input");
		mvwprintw(instr,0,1,"gre obsluguje sie przez wybranie odpowiedniej komendy");
		mvwprintw(instr,1,1,"m - podaj ruch (pole startowe, pole docelowe), s - zapisz, esc - wyjdz");
		mvwprintw(instr,2,1,"figury biale: x1, figury czarne: x0, wygrywa gracz ktory zbije krola przeciwnika");
		
		wrefresh(mboard);
		wrefresh(moves);
		wrefresh(input);
		wrefresh(instr);
		refresh();
		
		switch(ch)
		{
			case '\e':
				break;
			case 'm':
				mvwprintw(input,1,1,"            ");
				mvwprintw(input,1,1,"");
				my_getline(userinput, input);
				if(game.move(userinput))
				{
					save.write(userinput);
					p1=!p1;
				}
				else mvwprintw(input,1,1,"not a valid move");
				refresh();
				break;
			case 's':
				save.save();
				break;
		}
	}
		
	endwin();
	return 0;
}




void fillBoard(WINDOW *win, board &b, int height, int width, bool rotate)
{
	string board=b.getState();
	char sq[3]="xx";
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			sq[0]=board[(8*i+j)*2];
			sq[1]=board[(8*i+j)*2+1];
			mvwprintw(win,height/8*i+1,width/8*j+2,sq);
			if(height>22)mvwprintw(win,height/8*i+1,width/8*j+2,sq);
		}
	}
	if(height>22)
	{
		char sq2[5]="(xx)";
		for(int i=0; i<8; i++)
		{
			for(int j=0; j<8; j++)
			{
				if(rotate)
				{
					sq2[1]='a'+j;
					sq2[2]='1'+(7-i);
				}
				else
				{
					sq2[1]='a'+(7-j);
					sq2[2]='1'+i;
				}
				mvwprintw(win,height/8*i+2,width/8*j+2,sq2);
			}
		}
	}
	int mate=board[128];
	if(mate==-1)
	{
		mvwprintw(win,height/2,width/2-5,"black has won");
	}
	else if(mate==1)
	{
		mvwprintw(win,height/2,width/2-5,"white has won");
	}
}

