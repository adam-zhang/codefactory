#include "Notice.h"

using namespace std;

string Notice::usage()
{
	return "Usage: codefactory --arguments\n"
		"\t--class <class_name>	produce a class which named class_name\n"
		"\t--project 		produce a simple project which contains files main.cpp and CMakeFile.txt\n"
		"\t--singleton		produce a file contains a singleton class\n"
		"\t--threadpool		produce the files for thread pool\n";
}
