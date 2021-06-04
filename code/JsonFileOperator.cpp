/********************************************************************************
> FileName:	JsonFileOperator.cpp
> Author:	Mingping Zhang
> Email:	mingpingzhang@163.com
> Create Time:	Fri Jun 04 11:19:19 2021
********************************************************************************/

#include "JsonFileOperator.h"
#include <fstream>
#include <sstream>

JsonFileOperator::JsonFileOperator()
{
}

JsonFileOperator::~JsonFileOperator()
{
}


std::string JsonFileOperator::read(const std::string& fileName)
{

	std::ifstream file(fileName);
	if (!file.good())
		return std::string();
	std::stringstream ss;
	ss << file.rdbuf();
	return ss.str();
}
void JsonFileOperator::write(const std::string& fileName, const std::string& data)
{
	std::ofstream file(fileName);
	if (!file.good())
		return;
	file << data;
}
