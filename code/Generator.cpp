#include "Generator.h"
#include "algorithm.h"
#include <fstream>
#include <sstream>

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


bool generateQtCMakeFile(const string& projectName)
{
	ofstream file("CMakeLists.txt");
	if (!file)
		return false;
	stringstream ss;
	ss << "cmake_minimum_required(VERSION 3.1.0)\n"
		<< "project(" << projectName << ")\n"
		<< "set(CMAKE_INCLUDE_CURRENT_DIR ON)\n"
		<< "set(CMAKE_AUTOMOC ON)\n"
		<< "find_package(Qt5Widgets CONFIG REQUIRED)\n"
		<< "set(sources main.cpp\n"
		<< "\tMainWindow.cpp)\n"
		<< "add_executable(${PROJECT_NAME} ${sources})\n"
		<< "target_link_libraries(${PROJECT_NAME} Qt5::Widgets)";
	file << ss.str();
	return true;
}


string generateMainContent()
{
	stringstream ss;
	ss << "#include <QApplication>\n"
		<< "#include \"MainWindow.h\""
		<< "\n"
		<< "int main(int argc, char** argv)\n"
		<< "\{\n"
		<< "\tQApplication a(argc, argv);\n"
		<< "\tMainWindow w;\n"
		<< "\tw.show();\n"
		<< "\treturn a.exec();\n"
		<< "}";
	return ss.str();
}

bool generateQtMainFile()
{
	ofstream file("main.cpp");
	if (!file)
		return false;
	file << generateMainContent();
	return true;
}

bool generateMainWindowHeadFile()
{
	ofstream file("MainWindow.h");
	if (!file)
		return false;	
	stringstream ss;
	ss << "#ifndef __MAINWINDOW__H\n"
		<< "#define __MAINWINDOW__H\n"
		<< "#include <QMainWindow>\n"
		<< "\n"
		<< "class MainWindow : public QMainWindow\n"
		<< "{\n"
		<< "\tQ_OBJECT\n"
		<< "public:\n"
		<< "\tMainWindow();\n"
		<< "\t~MainWindow();\n"
		<< "};\n\n"
		<< "#endif//__MAINWINDOW__H";
	file << ss.str();
	return true;
}

bool generateMainWindowCpp()
{
	return generateCppFile("MainWindow");
}

bool generateMainWindowFiles()
{
	return generateMainWindowHeadFile() && generateMainWindowCpp();
}


bool generateQtProject(const string& projectName)
{
	return generateQtCMakeFile(projectName) && generateQtMainFile() && generateMainWindowFiles();
}

const std::string content()
{
	return	"#ifndef __SINGLETON__H\n" 
		"#define __SINGLETON__H\n"
		"\n"
		"#include <memory>\n"
		"#include <mutex>\n"
		"\n"
		"class FakeLock\n"
		"{\n"
		"	public:\n"
		"		FakeLock() {}\n"
		"		~FakeLock() {}\n"
		"	public:\n"
		"		void lock() {}\n"
		"		void unlock() {}\n"
		"};\n"
		"\n"
		"class RealLock\n"
		"{\n"
		"		std::mutex mutex_;\n"
		"	public:\n"
		"		void lock()\n"
		"		{\n"
		"			mutex_.lock();\n"
		"		}\n"
		"\n"
		"		void unlock()\n"
		"		{\n"
		"			mutex_.unlock();\n"
		"		}\n"
		"\n"
		"};\n"
		"\n"
		"template<typename T, typename Lock = FakeLock>\n"
		"class Singleton\n"
		"{\n"
		"public:\n"
		"	Singleton() {}\n"
		"	~Singleton() {}\n"
		"private:\n"
		"	static T* instance_;\n"
		"public:\n"
		"	static T& instance()\n"
		"	{\n"
		"		if (!instance_)\n"
		"		{\n"
		"			Lock lock;\n"
		"			lock.lock();\n"
		"			if (!instance_)\n"
		"			{\n"
		"				instance_ = new T;\n"
		"			}\n"
		"			lock.unlock();\n"
		"		}\n"
		"		return *instance_;\n"
		"	}\n"
		"};\n"
		"\n"
		"template<typename T, typename Lock>\n"
		"T* Singleton<T, Lock>::instance_ = 0;\n"
		"\n"
		"#endif//__SINGLETON__H\n"
		"\n";
}

void writeFileContent(const std::string& fileName, const std::string& content)
{
	std::ofstream file(fileName);
	if (!file.good())
		return;
	file << content << std::endl;
}

bool generateSingleton()
{
	auto fileName = "Singleton.h";
	writeFileContent(fileName, content());
	return true;
}

string threadPoolHeader()
{
	return	"#ifndef __THREADPOOL__H\n"
		"#define __THREADPOOL__H\n"
		"\n"
		"#include <vector>\n"
		"#include <functional>\n"
		"#include <thread>\n"
		"#include <mutex>\n"
		"#include <queue>\n"
		"#include <condition_variable>\n"
		"#include <atomic>\n"
		"\n"
		"class ThreadPool\n"
		"{\n"
		"public:\n"
		"	explicit ThreadPool(int count);\n"
		"	ThreadPool(const ThreadPool&) =delete;\n"
		"	ThreadPool& operator=(const ThreadPool&) = delete;\n"
		"	~ThreadPool();\n"
		"public:\n"
		"	using Task = std::function<void()>;\n"
		"public:\n"
		"	void start();\n"
		"	void stop();\n"
		"	void append(const Task& task);\n"
		"private:\n"
		"	int threadCount_;\n"
		"	std::vector<std::thread> threads_;\n"
		"	std::mutex mutex_;\n"
		"	std::queue<Task> tasks_;\n"
		"	std::condition_variable condition_;\n"
		"	std::atomic<bool> isRunning_;\n"
		"private:\n"
		"	void work();\n"
		"};\n"
		"#endif//__THREADPOOL__H\n";
}

string threadPoolImpletement()
{
	return "#include \"ThreadPool.h\"\n"
		"#include <iostream>\n"
		"\n"
		"ThreadPool::ThreadPool(int count)\n"
		"	: threadCount_(count)\n"
		"	  , isRunning_(false)\n"
		"{\n"
		"}\n"
		"\n"
		"ThreadPool::~ThreadPool()\n"
		"{\n"
		"}\n"
		"\n"
		"void ThreadPool::start()\n"
		"{\n"
		"	isRunning_ = true;\n"
		"	for(int i = 0; i != threadCount_; ++i)\n"
		"		threads_.emplace_back(std::thread(&ThreadPool::work, this));\n"
		"}\n"
		"\n"
		"void ThreadPool::work()\n"
		"{\n"
		"	while(isRunning_)\n"
		"	{\n"
		"		Task task;\n"
		"		std::unique_lock<std::mutex> lock(mutex_);\n"
		"		if (!tasks_.empty())\n"
		"		{\n"
		"			task = tasks_.front();\n"
		"			tasks_.pop();\n"
		"		}\n"
		"		else if(isRunning_ && tasks_.empty())\n"
		"			condition_.wait(lock);\n"
		"		if (task)\n"
		"			task();\n"
		"	}\n"
		"}	\n"
		"\n"
		"void ThreadPool::stop()\n"
		"{\n"
		"	{\n"
		"		std::unique_lock<std::mutex> lock;\n"
		"		isRunning_ = false;\n"
		"		condition_.notify_all();\n"
		"	}\n"
		"	for(std::thread& t : threads_)\n"
		"		if (t.joinable())\n"
		"			t.join();\n"
		"}\n"
		"\n"
		"void ThreadPool::append(const Task& task)\n"
		"{\n"
		"	if (isRunning_)\n"
		"	{\n"
		"		std::unique_lock<std::mutex> lock;\n"
		"		tasks_.push(task);\n"
		"		condition_.notify_one();\n"
		"	}\n"
		"}\n";
}

void generateThreadPoolHeaderFile()
{
	auto fileName = "ThreadPool.h";
	writeFileContent(fileName, threadPoolHeader());
}

void generateThreadPoolImpletementFile()
{
	auto fileName = "ThreadPool.cpp";
	writeFileContent(fileName, threadPoolImpletement());
}

bool generateThreadPool()
{
	generateThreadPoolHeaderFile();
	generateThreadPoolImpletementFile();
	return true;
}

string properties()
{
	return	"#ifndef __PROPERTIES__H\n"
		"#define __PROPERTIES__H\n"
		"\n"
		"#define PROPERTY(type, name, method) \\\n"
		"         private: \\\n"
		"                  type name##_; \\\n"
		"         public: \\\n"
		"                  const type& name()const \\\n"
		"                  { return name##_; } \\\n"
		"                  void method(const type& value) \\\n"
		"                  { name##_ = value; }\n"
		"#endif//__PROPERTIES__H\n";
}

bool generateProperties()
{
	auto fileName = "Properties.h";
	writeFileContent(fileName, properties());
	return true;
}

string queue()
{
	return "#ifndef __QUEUE__H\n"
		"#define __QUEUE__H \n"
		"\n"
		"#include <queue>\n"
		"#include <mutex>\n"
		"#include <condition_variable>\n"
		"#include <initializer_list>\n"
		"#include <iostream>\n"
		"\n"
		"template<typename T>\n"
		"class Queue\n"
		"{\n"
		"	private:\n"
		"		std::mutex mutex_;\n"
		"		std::condition_variable condition_;\n"
		"		std::queue<T> data_;\n"
		"	public:\n"
		"		Queue()=default;\n"
		"		Queue(const Queue&)=delete;\n"
		"		Queue& operator=(const Queue&)=delete;\n"
		"\n"
		"		void push(const T& value)\n"
		"		{\n"
		"			std::lock_guard<std::mutex> lock(mutex_);\n"
		"			data_.push(value);\n"
		"			condition_.notify_one();\n"
		"		}\n"
		"\n"
		"		T pop( )\n"
		"		{\n"
		"			std::unique_lock<std::mutex> lock(mutex_);\n"
		"			while(data_.empty())\n"
		"				condition_.wait(lock);\n"
		"			T value = data_.front();\n"
		"			data_.pop();\n"
		"			return value;\n"
		"		}\n"
		"\n"
		"		size_t size() \n"
		"		{\n"
		"			std::lock_guard<std::mutex> lock(mutex_);\n"
		"			return data_.size();\n"
		"		}\n"
		"}; \n"
		"\n"
		"#endif//__QUEUE__H\n";
}

bool generateQueue()
{
	writeFileContent("Queue.h", queue());
	return true;
}
