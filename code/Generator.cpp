#include "Generator.h"
#include "algorithm.h"
#include <fstream>
//#ifdef WIN32
//#include <windows.h>
//#else
//#include <sys/stat.h>
//#include <sys/types.h>
//#endif

using namespace std;

static bool generateCppFile(const string& className)
{
	ofstream file(className + ".cpp");
	if (!file)
		return false;
	file << "#include \"" << className << ".h\"\n\n"
		<< className << "::" << className << "()\n"
		<< "{\n"
		<< "}\n\n"
		<< className << "::~" << className << "()\n"
		<< "{\n"
		<< "}";
	return true;	
}

static bool generateHeadFile(const string& className)
{
	ofstream file(className + ".h");
	if (!file)
		return false;
	file << "#ifndef __" << toUpper(className) << "__H\n" 
		<<"#define __" << toUpper(className) << "__H\n"
		<< "\n\n"
		<< "class " << className << "\n"
		<< "{\n"
		<< "public:\n"
		<< "\t" << className << "();\n"
		<< "\t~" << className << "();\n"
		<< "};\n"
		<<"#endif//__" << toUpper(className) << "__H" << endl;
	return true;
}

bool generateClass(const string& className)
{
	return generateHeadFile(className) && generateCppFile(className);
	return true;
}

static bool generateCMakeFile(const std::string& projectName)
{
	ofstream file("CMakeLists.txt");
	if (!file)
		return false;
	file << "cmake_minimum_required(VERSION 2.8)\n"
		<< "project(" << projectName << ")\n"
		<< "set(sources main.cpp)\n"
		<< "add_executable(${PROJECT_NAME} ${sources})";
	return true;
}

static bool generateMainFile()
{
	ofstream file("main.cpp");
	if (!file)
		return false;
	file << "#include <iostream>\n"
		<< "\nusing namespace std;\n"
		<< "\n"
		<< "int main(int argc, char** argv)\n"
		<< "{\n"
		<< "\tcout << \"Hello World.\" << endl;\n"
		<< "\treturn 0;\n"
		<< "}";
	return true;
}

//static bool generateDirectory(const string& projectName)
//{
//#ifdef WIN32
//	CreateDirectoryA(projectName.c_str(), 0);
//#else
//	mkdir(projectName.c_str());
//#endif
//	return true;
//}

bool generateProject(const string& projectName)
{
       	return generateCMakeFile(projectName) && generateMainFile();
}
