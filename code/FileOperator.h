/********************************************************************************
> FileName:	FileOperator.h
> Author:	Mingping Zhang
> Email:	mingpingzhang@163.com
> Create Time:	Tue Jun 08 13:26:15 2021
********************************************************************************/
#ifndef FILEOPERATOR_H
#define FILEOPERATOR_H

#include <string>

class FileOperator
{
public:
	FileOperator();
	~FileOperator();

	static bool writeTo(const std::string& fileName, const std::string& content);
};
#endif//FILEOPERATOR_H
