/********************************************************************************
> FileName:	JsonParser.h
> Author:	Mingping Zhang
> Email:	mingpingzhang@163.com
> Create Time:	Fri Jun 04 10:50:12 2021
********************************************************************************/
#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <string>
#include <memory>

class AuthorInfo;

class JsonParser
{
private:
	JsonParser();
	~JsonParser();

	std::unique_ptr<AuthorInfo> parseAuthorInfo(const std::string& data);
};
#endif//JSONPARSER_H
