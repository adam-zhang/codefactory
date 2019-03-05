#include "CommandLineAnalyzer.h"

using namespace std;

static vector<string> makeVector(int argc, char** argv)
{
	vector<string> v;
	for(int i = 0; i != argc; ++i)
		v.push_back(argv[i]);
	return v;
}

CommandLineAnalyzer::CommandLineAnalyzer(int argc, char** argv)
	: lines_(makeVector(argc, argv))
{
}

CommandLineAnalyzer::~CommandLineAnalyzer()
{
}


