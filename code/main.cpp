#include <iostream>
#include "CommandLineAnalyzer.h"
#include "Logger.h"
#include "Notice.h"
#include "Generator.h"
#include <map>
#include <functional>
#include "Printer.h"

using namespace std;

int dealOneArgument(const CommandLineAnalyzer&)
{
	Logger::output(Notice::usage());
	return 0;
}

bool showHelp()
{
	Logger::output(Notice::usage());
	return true;
}

int dealTwoArguments(const CommandLineAnalyzer& analyzer)
{
	auto m = map<string, function<bool()>>
	{
		{"--threadpool", generateThreadPool}
		, {"--queue", generateQueue}
		, {"--logger", generateLogger}
		, {"--properties", generateProperties}
		, {"--help", showHelp}
	};

	if (m.find(analyzer.argument(1)) != m.end())
		return m[analyzer.argument(1)]();
	Logger::output(Notice::usage());
	return 0;
}

int dealThreeArguments(const CommandLineAnalyzer& analyzer)
{
	auto m = map<string, function<bool(string)>>
	{
		{"--qtclass", generateQtClass}
		,{"--class", generateClass}
		,{"--qtproject", generateQtProject}
		,{"--openglproject", generateOpenGLProject}
		,{"--boostproject", generateBoostProject}
		,{"--project", generateProject}
		,{"--singleton", generateSingleton}
	};

	if (m.find(analyzer.argument(1)) != m.end())
		return m[analyzer.argument(1)](analyzer.argument(2));
	return 0;
}

int dealFourArguments(const CommandLineAnalyzer& analyzer)
{
	generateAuthorInfo(analyzer.argument(2), analyzer.argument(3));
	return 0;
}

int main(int argc, char** argv)
{
	CommandLineAnalyzer analyzer(argc, argv);
	auto m = map<int, function<int(const CommandLineAnalyzer&)>> 
	{
		{1, dealOneArgument},
			{2, dealTwoArguments},
			{3, dealThreeArguments},
			{4, dealFourArguments}
	};
	
	if (m.find(analyzer.argumentCount()) != m.end())
		return m[analyzer.argumentCount()](analyzer);
	return 0;
}
