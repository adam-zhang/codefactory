cmake_minimum_required(VERSION 3.5)
if (WIN32)
	set(CMAKE_INSTALL_PREFIX c:/windows/system32)
else()
	set (CMAKE_INSTALL_PREFIX /usr/bin)
endif()
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
	)
add_executable(${PROJECT_NAME} ${sources})
install(TARGETS codefactory DESTINATION /usr/bin)
