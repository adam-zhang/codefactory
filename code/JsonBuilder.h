/********************************************************************************
> FileName:	JsonBuilder.h
> Author:	Mingping Zhang
> Email:	mingpingzhang@163.com
> Create Time:	Fri Jun 04 11:09:51 2021
********************************************************************************/
#ifndef JSONBUILDER_H
#define JSONBUILDER_H

#include <string>
#include <memory>

class AuthorInfo;

class JsonBuilder
{
private:
	JsonBuilder();
	~JsonBuilder();

public:
	static std::string build(const std::unique_ptr<AuthorInfo>&);
};
#endif//JSONBUILDER_H
