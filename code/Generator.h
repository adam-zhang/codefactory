#ifndef __GERNERATOR__H
#define __GERNERATOR__H

#include <string>

bool generateClass(const std::string& name);
bool generateProject(const std::string& name);
bool generateQtProject(const std::string& name);
bool generateOpenGLProject(const std::string& name);
bool generateBoostProject(const std::string& name);
bool generateSingleton(const std::string&);
bool generateThreadPool();
bool generateProperties();
bool generateQueue();
bool generateLogger();
bool generateAuthorInfo(const std::string& author, const std::string& email);
bool generateQtClass(const std::string& className);
void test();
#endif//__GERNERATOR_
