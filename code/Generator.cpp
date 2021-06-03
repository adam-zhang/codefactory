#include "Generator.h"
#include "algorithm.h"
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>

using namespace std;

string currentTime()
{
	std::time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
	return ctime(&tt);
}

static string authorInfo(const string& fileName)
{
	return "/********************************************************************************\n"
		"> FileName:\t" + fileName +
		"\n> Author:\tMingping Zhang\n"
		"> Email:\tmingpingzhang@163.com\n" + 
		"> Create Time:\t" + currentTime() +
		"********************************************************************************/\n";
}

static std::string warning()
{
	return "add_definitions(-W -Wall -std=c++11)\n";
}


static bool generateCppFile(const string& className)
{
	ofstream file(className + ".cpp");
	if (!file)
		return false;
	file << authorInfo(className + ".cpp") 
		<< "\n"
		<< "#include \"" << className << ".h\"\n\n"
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
	file << authorInfo(className + ".h")
		<< "#ifndef " << toUpper(className) << "_H\n" 
		<<"#define " << toUpper(className) << "_H\n"
		<< "\n\n"
		<< "class " << className << "\n"
		<< "{\n"
		<< "public:\n"
		<< "\t" << className << "();\n"
		<< "\t~" << className << "();\n"
		<< "};\n"
		<<"#endif//" << toUpper(className) << "_H" << endl;
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
	file << "cmake_minimum_required(VERSION 3.0)\n"
		<< "project(" << projectName << ")\n"
		<< warning() 
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
		<< "int main(int /*argc*/, char** /*argv*/)\n"
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
		<< warning()
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
	ss << "#ifndef MAINWINDOW_H\n"
		<< "#define MAINWINDOW_H\n"
		<< "#include <QMainWindow>\n"
		<< "\n"
		<< "class MainWindow : public QMainWindow\n"
		<< "{\n"
		<< "\tQ_OBJECT\n"
		<< "public:\n"
		<< "\tMainWindow(QWidget* parent = 0);\n"
		<< "\t~MainWindow();\n"
		<< "};\n\n"
		<< "#endif//MAINWINDOW_H";
	file << ss.str();
	return true;
}

bool generateMainWindowCpp()
{
	ofstream file("MainWindow.cpp");
	if (!file)
		return false;
	stringstream ss;
	ss << "#include \"MainWindow.h\"\n\n"
		<< "MainWindow::MainWindow(QWidget* parent)\n"
		<< "\t:QMainWindow(parent)\n"
		<< "{\n"
		<< "};\n\n"
		<< "MainWindow::~MainWindow()\n"
		<< "{\n}";
	file << ss.str();
	return true;
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
	return	"#ifndef SINGLETON_H\n" 
		"#define SINGLETON_H\n"
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
		"#endif//SINGLETON_H\n"
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
	return	"#ifndef THREADPOOL_H\n"
		"#define THREADPOOL_H\n"
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
		"#endif//THREADPOOL_H\n";
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
	return	"#ifndef PROPERTIES_H\n"
		"#define PROPERTIES_H\n"
		"\n"
		"#define PROPERTY(type, name, method) \\\n"
		"         private: \\\n"
		"                  type name##_; \\\n"
		"         public: \\\n"
		"                  const type& name()const \\\n"
		"                  { return name##_; } \\\n"
		"                  void method(const type& value) \\\n"
		"                  { name##_ = value; }\n"
		"#endif//PROPERTIES_H\n";
}

bool generateProperties()
{
	auto fileName = "Properties.h";
	writeFileContent(fileName, properties());
	return true;
}

string queue()
{
	return "#ifndef QUEUE_H\n"
		"#define QUEUE_H \n"
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
		"#endif//QUEUE_H\n";
}

bool generateQueue()
{
	writeFileContent("Queue.h", queue());
	return true;
}

void generateSourceFile()
{
	auto content = "#include <GLFW/glfw3.h>\n"
		"int main(void)\n"
		"{\n"
		"    GLFWwindow* window;\n"
		"    /* Initialize the library */\n"
		"    if (!glfwInit())\n"
		"        return -1;\n"
		"    /* Create a windowed mode window and its OpenGL context */\n"
		"    window = glfwCreateWindow(640, 480, \"Hello World\", NULL, NULL);\n"
		"    if (!window)\n"
		"    {\n"
		"        glfwTerminate();\n"
		"        return -1;\n"
		"    }\n"
		"    /* Make the window's context current */\n"
		"    glfwMakeContextCurrent(window);\n"
		"    /* Loop until the user closes the window */\n"
		"    while (!glfwWindowShouldClose(window))\n"
		"    {\n"
		"        /* Render here */\n"
		"        glClear(GL_COLOR_BUFFER_BIT);\n"
		"        /* Swap front and back buffers */\n"
		"        glfwSwapBuffers(window);\n"
		"        /* Poll for and process events */\n"
		"        glfwPollEvents();\n"
		"    }\n"
		"    glfwTerminate();\n"
		"    return 0;\n"
		"}\n";
	writeFileContent("main.cpp", content);
}

void generateOpenGLCMakeFile(const std::string& name)
{
	string content = "cmake_minimum_required(VERSION 2.8)\n"
		"project(glTest)\n"
		"find_package(OpenGL REQUIRED)\n"
		+ warning() +
		"include_directories(${OpenGL_INCLUDE_DIRS})\n"
		"link_directories(${OpenGL_LIBRARY_DIRS})\n"
		"add_definitions(${OpenGL_DEFINITIONS})\n"
		"find_package(glfw3 REQUIRED)\n"
		"set(sources main.cpp)\n"
		"add_executable(${PROJECT_NAME} ${sources})\n"
		"target_link_libraries(${PROJECT_NAME} glfw3 dl pthread GL)\n";
	writeFileContent("CMakeLists.txt", content);
}

bool generateOpenGLProject(const std::string& name)
{
	generateOpenGLCMakeFile(name);
	generateSourceFile();
	return true;
}

std::string loggerHeader()
{
	return "#ifndef LOGGER_H\n"
		"#define LOGGER_H\n"
		"\n"
		"#include <string>\n"
		"#include <sstream>\n"
		"\n"
		"class Logger\n"
		"{\n"
		"private:\n"
		"	Logger();\n"
		"	~Logger();\n"
		"public:\n"
		"	static void write(const std::string& text);\n"
		"	template<typename T>\n"
		"	static void write(const std::string& note, const T& value)\n"
		"	{\n"
		"		std::stringstream ss;\n"
		"		ss << note << \":\" << value;		\n"
		"		write(ss.str());\n"
		"	}\n"
		"};\n"
		"#endif//LOGGER_H";
}

std::string loggerCpp()
{
	return "#include \"Logger.h\"\n"
		"#include <chrono>\n"
		"#include <iomanip>\n"
		"#include <fstream>\n"
		"\n"
		"using namespace std;\n"
		"using namespace chrono;\n"
		"\n"
		"Logger::Logger()\n"
		"{\n"
		"}\n"
		"\n"
		"Logger::~Logger()\n"
		"{\n"
		"}\n"
		"\n"
		"static string getFileName()\n"
		"{\n"
		"	auto current = system_clock::now();\n"
		"	auto t = system_clock::to_time_t(current);\n"
		"	stringstream ss;\n"
		"	ss << put_time(localtime(&t), \"%Y-%m-%d\");\n"
		"	return ss.str();\n"
		"}\n"
		"\n"
		"static int getMilliseconds(const time_point<system_clock>& current)\n"
		"{\n"
		"        auto s = duration_cast<seconds>(current.time_since_epoch()).count();\n"
		"	auto millis = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();\n"
		"	return millis - s * 1000;\n"
		"}\n"
		"\n"
		"static string getTime()\n"
		"{\n"
		"	auto current = system_clock::now();\n"
		"	auto t = system_clock::to_time_t(current);\n"
		"	stringstream ss;\n"
		"	ss << put_time(localtime(&t), \"%H:%M:%S.\") << setw(3) << setfill('0') << getMilliseconds(current);\n"
		"	return ss.str();\n"
		"}\n"
		"\n"
		"\n"
		"\n"
		"static void writeToFile(const string& fileName, const string& text )\n"
		"{\n"
		"	ofstream file(fileName, ios_base::app);\n"
		"	file << getTime() << \"\\t\" << text << \"\\n\";\n"
		"}\n"
		"\n"
		"void Logger::write(const string& text)\n"
		"{\n"
		"	writeToFile(getFileName(), text);\n"
		"}\n";
}

static void generateLoggerHeader()
{
	writeFileContent("Logger.h", loggerHeader());
}

static void generateLoggerCpp()
{
	writeFileContent("Logger.cpp", loggerCpp());
}

bool generateLogger()
{
	generateLoggerHeader();
	generateLoggerCpp();
	return true;
}

std::string contentBoostCMake(const std::string& name)
{
	return "cmake_minimum_required(VERSION 3.0)\n"
		"project(" + name + ")\n"
		+ warning() + 
		"find_package(Boost REQUIRED COMPONENTS system thread)\n"
		"include_directories(${Boost_INCLUDE_DIRS})\n"
		"set(sources main.cpp)\n"
		"add_executable(${PROJECT_NAME} ${sources})\n"
		"target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})\n";
}

static void generateBoostCMakeFile(const std::string& name)
{
	writeFileContent("CMakeLists.txt", contentBoostCMake(name));
}

bool generateBoostProject(const std::string& name)
{
	generateBoostCMakeFile(name);
	generateMainFile();
	return true;
}
