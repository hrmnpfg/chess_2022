#include "square.hpp"
#include "piece.hpp"
#include "board.hpp"
#include <string>
#include <cmath>

using namespace std;

board::board()
{
	turn=false;
	string name="a1";
	for(int i=0;i<8;i++)
	{
		name[1]='1';
		for(int j=0;j<8;j++)
		{
			tab[i][j]=new square(name);
			name[1]++;
		}
		name[0]++;
	}
	checkMate=0;
	for(int i=0;i<8;i++) tab[i][1]->placePiece("pawn",true);
	tab[0][0]->placePiece("rook",true);
	tab[1][0]->placePiece("knight",true);
	tab[2][0]->placePiece("bishop",true);
	tab[3][0]->placePiece("queen",true);
	tab[4][0]->placePiece("king",true);
	tab[5][0]->placePiece("bishop",true);
	tab[6][0]->placePiece("knight",true);
	tab[7][0]->placePiece("rook",true);
	for(int i=0;i<8;i++) tab[i][6]->placePiece("pawn",false);
	tab[0][7]->placePiece("rook",false);
	tab[1][7]->placePiece("knight",false);
	tab[2][7]->placePiece("bishop",false);
	tab[3][7]->placePiece("queen",false);
	tab[4][7]->placePiece("king",false);
	tab[5][7]->placePiece("bishop",false);
	tab[6][7]->placePiece("knight",false);
	tab[7][7]->placePiece("rook",false);
}

board::~board()
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			delete(tab[i][j]);
		}
	}
}

void board::show()
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(!turn) cout << tab[j][7-i]->getContents() << " ";
			else cout << tab[7-j][i]->getContents() << " ";
		}
		cout << endl;
	}
	cout << endl;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(!turn) cout << tab[j][7-i]->name << " ";
			else cout << tab[7-j][i]->name << " ";
		}
		cout << endl;
	}
}

string board::getState()
{
	string s="";
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(!turn) s = s + tab[j][7-i]->getContents();
			else s = s + tab[7-j][i]->getContents();
		}
	}
	s = s + char(checkMate);
	return s;
}

bool board::checkKnight(char t, int i, int j)
{
	if(i<0||i>7||j<0||j>7) return false;
	if(tab[i][j]->getContents()[0]=='K' && tab[i][j]->getContents()[1]!=t) return true;
	return false;
}

bool board::checkAttacked(square *s)
{
	char t='0';
	if(!turn) t='1';
	
	int a=s->name[0]-'a';
	int b=s->name[1]-'1';
	
	for(int i=-1;i<2;i++)
	{
		for(int j=-1;j<2;j++)
		{
			if(i==0&&j==0) continue;
			int temp1=a+i;
			int temp2=b+j;
			if(temp1<0||temp1>7||temp2<0||temp2>7) continue;
			if(tab[temp1][temp2]->getContents()[0]=='K' && tab[temp1][temp2]->getContents()[1]!=t) return true;
			if(i==j || i==-j)
			{
				if(tab[temp1][temp2]->getContents()[0]=='P')
				{
					if(tab[temp1][temp2]->getContents()[1]!=t)
					{
						if(turn && temp2<b) return true;
						if(!turn && temp2>b) return true;
					} 
				}
			}
		}
	}
	
	if(checkKnight(t,a+2,b+1)) return true;
	if(checkKnight(t,a+2,b-1)) return true;
	if(checkKnight(t,a-2,b+1)) return true;
	if(checkKnight(t,a-2,b-1)) return true;
	if(checkKnight(t,a+1,b+2)) return true;
	if(checkKnight(t,a-1,b+2)) return true;
	if(checkKnight(t,a+1,b-2)) return true;
	if(checkKnight(t,a-2,b-2)) return true;
	
	int i;
	int j;
	string temp;
	
	i=a+1;
	j=b;
	while(i<8)
	{
		temp=tab[i][j]->getContents();
		if(temp=="  ")
		{
			i++;
			continue;
		}
		if(temp[1]!=t)
		{
			if(temp[0]=='Q'||temp[0]=='R') return true;
		}
		break;
	}
	i=a-1;
	j=b;
	while(i>-1)
	{
		temp=tab[i][j]->getContents();
		if(temp=="  ")
		{
			i--;
			continue;
		}
		if(temp[1]!=t)
		{
			if(temp[0]=='Q'||temp[0]=='R') return true;
		}
		break;
	}
	i=a;
	j=b+1;
	while(j<8)
	{
		temp=tab[i][j]->getContents();
		if(temp=="  ")
		{
			j++;
			continue;
		}
		if(temp[1]!=t)
		{
			if(temp[0]=='Q'||temp[0]=='R') return true;
		}
		break;
	}
	i=a;
	j=b-1;
	while(j>-1)
	{
		temp=tab[i][j]->getContents();
		if(temp=="  ")
		{
			j--;
			continue;
		}
		if(temp[1]!=t)
		{
			if(temp[0]=='Q'||temp[0]=='R') return true;
		}
		break;
	}
	i=a+1;
	j=b+1;
	while(i<8 && j<8)
	{
		temp=tab[i][j]->getContents();
		if(temp=="  ")
		{
			i++;
			j++;
			continue;
		}
		if(temp[1]!=t)
		{
			if(temp[0]=='Q'||temp[0]=='B') return true;
		}
		break;
	}
	i=a-1;
	j=b+1;
	while(i>-1 && j<8)
	{
		temp=tab[i][j]->getContents();
		if(temp=="  ")
		{
			i--;
			j++;
			continue;
		}
		if(temp[1]!=t)
		{
			if(temp[0]=='Q'||temp[0]=='B') return true;
		}
		break;
	}
	i=a-1;
	j=b+1;
	while(j<8 && i>-1)
	{
		temp=tab[i][j]->getContents();
		if(temp=="  ")
		{
			i--;
			j++;
			continue;
		}
		if(temp[1]!=t)
		{
			if(temp[0]=='Q'||temp[0]=='B') return true;
		}
		break;
	}
	i=a-1;
	j=b-1;
	while(j>-1 && i>-1)
	{
		temp=tab[i][j]->getContents();
		if(temp=="  ")
		{
			a--;
			j--;
			continue;
		}
		if(temp[1]!=t)
		{
			if(temp[0]=='Q'||temp[0]=='B') return true;
		}
		break;
	}
	return false;
}

bool board::move(string s)
{	// s = "xx xx"
	if(checkMate!=0) return false;
	for(int i=0;i<5;i++)
	{
		if(i==2) continue;
		if(s[i]>='a' && s[i]<='h' || s[i]>='1' && s[i]<='8') continue;
		return false;
	}
	string source=tab[s[0]-'a'][s[1]-'1']->getContents();
	string destination=tab[s[3]-'a'][s[4]-'1']->getContents();
	
	char t='0';
	if(turn) t='1';
	if(source[1] == t) return false;
	try
	{
		try
		{
			if(this->makeMove(*tab[s[0]-'a'][s[1]-'1'], *tab[s[3]-'a'][s[4]-'1']))
			{
				tab[s[0]-'a'][s[1]-'1']->move(tab[s[3]-'a'][s[4]-'1']);
				turn=!turn;
				return true;
			}
		}
		catch(runtime_error& e)
		{
			string event=e.what();
			if(event=="a0")
			{
				tab[s[0]-'a'][s[1]-'1']->move(tab[s[3]-'a'][s[4]-'1']);
				tab[0][s[1]-'1']->move(tab[4][s[1]-'1']);
				turn=!turn;
				return true;
			}
			if(event=="b0")
			{
				tab[s[0]-'a'][s[1]-'1']->move(tab[s[3]-'a'][s[4]-'1']);
				tab[7][s[1]-'1']->move(tab[5][s[1]-'1']);
				turn=!turn;
				return true;
			}
			if(event=="p1")
			{
				if(tab[s[3]-'a'][s[1]-'1']->getContents()[0]=='P' && tab[s[3]-'a'][s[1]-'1']->specialEvent())
				{
					tab[s[3]-'a'][s[1]-'1']->removePiece();
					tab[s[0]-'a'][s[1]-'1']->move(tab[s[3]-'a'][s[4]-'1']);
					turn=!turn;
					return true;
				}
			}
			if(event=="p2")
			{
				if(tab[s[0]-'a'][(s[1]-'1'+s[4]-'1')/2]->getContents()=="  ")
				{
					tab[s[0]-'a'][s[1]-'1']->move(tab[s[3]-'a'][s[4]-'1']);
					turn=!turn;
					return true;
				}
			}
		}
	}
	catch(int mate)
	{
		checkMate=mate;
	}
	return false;
}

bool board::makeMove(square a, square b)
{ 
	string source=a.getContents();
	string destination=b.getContents();
	if(a.name==b.name) return false;
	
	if(source=="  ") return false;
	
	if(source[1]==destination[1]) return false;
	
	if(source[0]=='P')
	{
		if(destination!="  " && a.name[0]==b.name[0]) return false;
		if(destination=="  " && a.name[0]!=b.name[0] && a.makeMove(b)) throw runtime_error("p1");
		if(destination=="  " && a.name[0]==b.name[0] && abs(a.name[1]-b.name[1])==2) throw runtime_error("p2");
		if(destination=="  " && a.makeMove(b)) return true;
	}
	
	if(source[0]=='Q')
	{
		if(tab[a.name[0]-'a'][a.name[1]-'1']->makeMove(*tab[b.name[0]-'a'][b.name[1]-'1']))
		{
			int i=1;
			if(a.name[0]==b.name[0])
			{
				while((a.name[1]-'1'+i) < b.name[1]-'1')
				{
					if(tab[a.name[0]-'a'][a.name[1]-'1'+i]->getContents()!="  ") return false;
					i++;
				}
				i=-1;
				while((a.name[1]-'1'+i) > b.name[1]-'1')
				{
					if(tab[a.name[0]-'a'][a.name[1]-'1'+i]->getContents()!="  ") return false;
					i--;
				}
			}
			i=1;
			if(a.name[1]==b.name[1])
			{
				while((a.name[0]-'a'+i) < b.name[0]-'a')
				{
					if(tab[a.name[0]-'a'+i][a.name[1]-'1']->getContents()!="  ") return false;
					i++;
				}
				i=-1;
				while((a.name[0]-'a'+i) > b.name[0]-'a')
				{
					if(tab[a.name[0]-'a'-i][a.name[1]-'1']->getContents()!="  ") return false;
					i--;
				}
			}
			i=1;
			while((a.name[1]-'1'+i) < b.name[1]-'1' && (a.name[0]-'a'+i) < b.name[0]-'a')
			{
				if(tab[a.name[0]-'a'+i][a.name[1]-'1'+i]->getContents()!="  ") return false;
				i++;
			}	
			i=1;
			while((a.name[1]-'1'-i) > b.name[1]-'1' && (a.name[0]-'a'+i) < b.name[0]-'a')
			{
				if(tab[a.name[0]-'a'+i][a.name[1]-'1'-i]->getContents()!="  ") return false;
				i++;
			}
			i=1;
			while((a.name[1]-'1'+i) < b.name[1]-'1' && (a.name[0]-'a'-i) > b.name[0]-'a')
			{
				if(tab[a.name[0]-'a'-i][a.name[1]-'1'+i]->getContents()!="  ") return false;
				i++;
			}
			i=1;
			while((a.name[1]-'1'-i) > b.name[1]-'1' && (a.name[0]-'a'-i) > b.name[0]-'a')
			{
				cout << "repeat " << tab[a.name[0]-'a'-i][a.name[1]-'1'-i]->name;
				if(tab[a.name[0]-'a'-i][a.name[1]-'1'-i]->getContents()!="  ") return false;
				i++;
			}
			return true;
		}
	}
	
	if(source[0]=='K')
	{
		if(a.name[0]-b.name[0]==-2 && tab[a.name[0]-'a'][a.name[1]-'1']->makeMove(*tab[b.name[0]-'a'][b.name[1]-'1']))
		{
			if(tab[3][a.name[1]-'1']->getContents()=="  " && tab[2][a.name[1]-'1']->getContents()=="  " && tab[1][a.name[1]-'1']->getContents()=="  ")
			{
				if(!this->checkAttacked(tab[3][a.name[1]-'1']) &&  !this->checkAttacked(tab[2][a.name[1]-'1']))
				{
					if(tab[0][a.name[1]-'1']->specialEvent())
					{
						throw runtime_error("a0");
					}
				}
			}
		}
		
		if(a.name[0]-b.name[0]==2 && tab[a.name[0]-'a'][a.name[1]-'1']->makeMove(*tab[b.name[0]-'a'][b.name[1]-'1']))
		{
			if(tab[5][a.name[1]-'1']->getContents()=="  " && tab[6][a.name[1]-'1']->getContents()=="  ")
			{
				if(!this->checkAttacked(tab[5][a.name[1]-'1']) && !this->checkAttacked(tab[6][a.name[1]-'1']))
				{
					if(tab[7][a.name[1]-'1']->specialEvent())
					{
						throw runtime_error("b0");
					}
				}
			}
		}
		if(this->checkAttacked(tab[b.name[0]-'a'][b.name[1]-'1'])) return false;
		if(tab[a.name[0]-'a'][a.name[1]-'1']->makeMove(*tab[b.name[0]-'a'][b.name[1]-'1']))
		{
			return true;
		}
	}
	if(source[0]=='N')
	{
		if(tab[a.name[0]-'a'][a.name[1]-'1']->makeMove(*tab[b.name[0]-'a'][b.name[1]-'1']))
		{
			return true;
		}
	}
	if(source[0]=='R')
	{
		if(tab[a.name[0]-'a'][a.name[1]-'1']->makeMove(*tab[b.name[0]-'a'][b.name[1]-'1']))
		{
			int i=1;
			while((a.name[1]-'1'+i) < b.name[1]-'1')
			{
				if(tab[a.name[0]-'a'][a.name[1]-'1'+i]->getContents()!="  ") return false;
				i++;
			}
			i=-1;
			while((a.name[1]-'1'+i) > b.name[1]-'1')
			{
				if(tab[a.name[0]-'a'][a.name[1]-'1'+i]->getContents()!="  ") return false;
				i--;
			}
			i=1;
			while((a.name[0]-'1'+i) < b.name[0]-'1')
			{
				if(tab[a.name[0]-'a'+i][a.name[1]-'1']->getContents()!="  ") return false;
				i++;
			}
			i=-1;
			while((a.name[1]-'1'+i) > b.name[1]-'1')
			{
				if(tab[a.name[0]-'a'-i][a.name[1]-'1']->getContents()!="  ") return false;
				i--;
			}
			return true;
		}
	}
	if(source[0]=='B')
	{
		if(tab[a.name[0]-'a'][a.name[1]-'1']->makeMove(*tab[b.name[0]-'a'][b.name[1]-'1']))
		{
			int i=1;
			while((a.name[1]-'1'+i) < b.name[1]-'1' && (a.name[0]-'a'+i) < b.name[0]-'a')
			{
				if(tab[a.name[0]-'a'+i][a.name[1]-'1'+i]->getContents()!="  ") return false;
				i++;
			}	
			i=1;
			while((a.name[1]-'1'-i) > b.name[1]-'1' && (a.name[0]-'a'+i) < b.name[0]-'a')
			{
				if(tab[a.name[0]-'a'+i][a.name[1]-'1'-i]->getContents()!="  ") return false;
				i++;
			}
			i=1;
			while((a.name[1]-'1'+i) < b.name[1]-'1' && (a.name[0]-'a'-i) > b.name[0]-'a')
			{
				if(tab[a.name[0]-'a'-i][a.name[1]-'1'+i]->getContents()!="  ") return false;
				i++;
			}
			i=1;
			while((a.name[1]-'1'-i) > b.name[1]-'1' && (a.name[0]-'a'-i) > b.name[0]-'a')
			{
				cout << "repeat " << tab[a.name[0]-'a'-i][a.name[1]-'1'-i]->name;
				if(tab[a.name[0]-'a'-i][a.name[1]-'1'-i]->getContents()!="  ") return false;
				i++;
			}
			return true;
		}
	}
	return false;
}
	
