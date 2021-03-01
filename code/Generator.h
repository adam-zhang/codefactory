#ifndef __GERNERATOR__H
#define __GERNERATOR__H

#include <string>

bool generateClass(const std::string& name);
bool generateProject(const std::string& name);
bool generateQtProject(const std::string& name);
bool generateOpenGLProject(const std::string& name);
bool generateSingleton();
bool generateThreadPool();
bool generateProperties();
bool generateQueue();
#endif//__GERNERATOR_
