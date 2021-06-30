/********************************************************************************
> FileName:	FileOperator.cpp
> Author:	Mingping Zhang
> Email:	mingpingzhang@163.com
> Create Time:	Tue Jun 08 13:26:15 2021
********************************************************************************/

#include "FileOperator.h"
#include <fstream>

FileOperator::FileOperator()
{
}

FileOperator::~FileOperator()
{
}

bool FileOperator::writeTo(const std::string& fileName, const std::string& content)
{
	std::ofstream file(fileName);
	if (file.bad())
		return false;
	file << content;
	return true;
}
