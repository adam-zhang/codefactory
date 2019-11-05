#include <iostream>
#include "CommandLineAnalyzer.h"
#include "Logger.h"
#include "Notice.h"
#include "Generator.h"


int main(int argc, char** argv)
{
	CommandLineAnalyzer analyzer(argc, argv);
	if (analyzer.argumentCount() < 2)
	{
		Logger::output(Notice::usage());
		return 0;
	}
	if (analyzer.argument(1) == "--help")
	{
		Logger::output(Notice::usage());
		return 0;
	}
	if (analyzer.argument(1) == "--class")
	{
		generateClass(analyzer.argument(2));
		return 0;
	}
	if (analyzer.argument(1) == "--project")
	{
		generateProject(analyzer.argument(2));
	}
	if (analyzer.argument(1) == "--qtproject")
	{
		generateQtProject(analyzer.argument(2));
	}
	return 0;
}
