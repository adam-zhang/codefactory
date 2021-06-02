#ifndef __COMMANDLINEANALYZER__H
#define __COMMANDLINEANALYZER__H

#include <string>
#include <vector>

class CommandLineAnalyzer
{
	public:
		CommandLineAnalyzer(int argc, char** argv);
		~CommandLineAnalyzer();
	public:
		bool analyze();
	private:
		std::vector<std::string> lines_;
	public:
		int argumentCount()
		{ return (int)lines_.size();}
		const std::string argument(int index)const
		{ return lines_[index];}
};

#endif//__COMMANDLINEANALYZER__H
