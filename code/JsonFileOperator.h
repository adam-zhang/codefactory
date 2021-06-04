/********************************************************************************
> FileName:	JsonFileOperator.h
> Author:	Mingping Zhang
> Email:	mingpingzhang@163.com
> Create Time:	Fri Jun 04 11:19:19 2021
********************************************************************************/
#ifndef JSONFILEOPERATOR_H
#define JSONFILEOPERATOR_H

#include <string>

class JsonFileOperator
{
public:
	JsonFileOperator();
	~JsonFileOperator();

public:
	static std::string read(const std::string& fileName);
	static void write(const std::string& fileName, const std::string& data);
};
#endif//JSONFILEOPERATOR_H
