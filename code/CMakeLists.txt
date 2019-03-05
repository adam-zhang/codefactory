cmake_minimum_required(VERSION 2.8)
project(codefactory)
set(CMAKE_BUILD_TYPE Release)
set(sources main.cpp
	CommandLineAnalyzer.cpp
	Logger.cpp
	Notice.cpp
	Generator.cpp)
add_executable(${PROJECT_NAME} ${sources})
