/********************************************************************************
> FileName:	Library.h
> Author:	Mingping Zhang
> Email:	mingpingzhang@163.com
> Create Time:	Fri Jun 04 10:37:41 2021
********************************************************************************/
#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include "Properties.h"

class Library
{
public:
	Library();
	~Library();

	PROPERTY(std::string, packageName, setPackageName)
	PROPERTY(std::string, finding, setFinding)
	PROPERTY(std::string, includeDir, setIncludeDir)
	PROPERTY(std::string, library, setLibrary)
};
#endif//LIBRARY_H
