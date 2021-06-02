#include "Notice.h"

using namespace std;

string Notice::usage()
{
	return "Usage: codefactory --arguments\n"
		"\t--project <project_name>		produce a simple project which contains files main.cpp and CMakeFile.txt\n"
		"\t--openglproject <project_name>		produce a project for opengl\n"
		"\t--qtproject <project_name>		produce a project for Qt5\n"
		"\t--boostproject <project_name>		produce a project for boost\n"
		"\t--class <class_name>			produce a class which named class_name\n"
		"\t--singleton				produce a file contains a singleton class\n"
		"\t--threadpool				produce the files for thread pool\n"
		"\t--properties				produce a file contains a macro which can produce a property simply.\n"
		"\t--queue					produce a file onntains a thread safe queue.\n"
		"\t--logger				produce files for logger";
}
