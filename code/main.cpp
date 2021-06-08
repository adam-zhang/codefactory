#include <iostream>
#include "CommandLineAnalyzer.h"
#include "Logger.h"
#include "Notice.h"
#include "Generator.h"


int dealOneArgument()
{
	Logger::output(Notice::usage());
	return 0;
}

int dealTwoArguments(const CommandLineAnalyzer& analyzer)
{
	if (analyzer.argument(1) == "--singleton")
		generateSingleton();
	else if (analyzer.argument(1) == "--threadpool")
		generateThreadPool();
	else if (analyzer.argument(1) == "--properties")
		generateProperties();
	else if (analyzer.argument(1) == "--queue")
		generateQueue();
	else if (analyzer.argument(1) == "--logger")
		generateLogger();
	else if (analyzer.argument(1) == "--help")
		Logger::output(Notice::usage());
	else if (analyzer.argument(1) == "--test")
		test();
	else
		Logger::output(Notice::usage());
	return 0;
}

int dealThreeArguments(const CommandLineAnalyzer& analyzer)
{
	if (analyzer.argument(1) == "--class")
		generateClass(analyzer.argument(2));
	else if (analyzer.argument(1) == "--project")
		generateProject(analyzer.argument(2));
	else if (analyzer.argument(1) == "--qtproject")
		generateQtProject(analyzer.argument(2));
	else if (analyzer.argument(1) == "--openglproject")
		generateOpenGLProject(analyzer.argument(2));
	else if (analyzer.argument(1) == "--boostproject")
		generateBoostProject(analyzer.argument(2));
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
	switch(analyzer.argumentCount())
	{
		case 1:
			return dealOneArgument();
		case 2:
			return dealTwoArguments(analyzer);
		case 3:
			return dealThreeArguments(analyzer);
		case 4:
			return dealFourArguments(analyzer);
	}
	return 0;
}
