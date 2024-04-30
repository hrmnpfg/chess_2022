#include "history.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

history::history()
{
	fileName="save.txt";
}

history::history(string s)
{
	ifstream fs;
	fileName=s;
	fs.open(s,ifstream::in);
	if(!fs.good())
	{
		fileName="save.txt";
		fs.close();
	}
	else
	{
		string temp;
		while(true)
		{
			fs >> temp;
			if(fs.eof()) break;
			for(int i=0;i<s.length();i++)
			{
				if(s[i]=='&') s[i]=' ';
			}
			his.push_back(temp);
		}
		fs.close();
	}
}


void history::write(string s)
{
	for(int i=0;i<s.length();i++)
	{
		if(s[i]==' ') s[i]='&';
	}
	his.push_back(s);
}

string history::getLast(int n)
{
	if(his.size()-n-1<0 || his.size()-n-1>=his.size()) return "";
	else 
	{
		string s=his[his.size()-n-1];
		for(int i=0;i<s.length();i++)
		{
			if(s[i]=='&') s[i]=' ';
		}
		return s;
	}
}

void history::save()
{
	ofstream fs;
	fs.open(fileName,ofstream::out | ios::trunc);
	if(!fs.is_open()) throw runtime_error("error opening file: "+fileName);
	for(int i=0;i<his.size();i++)
	{
		fs << his[i] << endl;
	}
	fs.close();
}
