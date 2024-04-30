#ifndef HISTORY_HPP
#define HISTORY_HPP
#include <vector>
#include <string>

class history
{
private:
	std::vector<std::string> his;
	std::string fileName;
	
public:
	history();
	history(std::string s);
	
	void write(std::string s);
	std::string getLast(int n);
	void save();
};

#endif
