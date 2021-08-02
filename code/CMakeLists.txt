cmake_minimum_required(VERSION 3.5)
add_compile_options(-std=c++11)
project(codefactory)
set(CMAKE_BUILD_TYPE Release)
set(sources main.cpp
	CommandLineAnalyzer.cpp
	Logger.cpp
	Notice.cpp
	Generator.cpp
	Library.cpp
	AuthorInfo.cpp
	JsonParser.cpp
	JsonBuilder.cpp
	JsonFileOperator.cpp
	FileOperator.cpp
	)
add_executable(${PROJECT_NAME} ${sources})
install(TARGETS codefactory DESTINATION /usr/bin)
