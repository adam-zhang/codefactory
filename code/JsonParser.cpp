/********************************************************************************
> FileName:	JsonParser.cpp
> Author:	Mingping Zhang
> Email:	mingpingzhang@163.com
> Create Time:	Fri Jun 04 10:50:12 2021
********************************************************************************/

#include "JsonParser.h"
#include "AuthorInfo.h"
#include "nlohmann/json.hpp"

JsonParser::JsonParser()
{
}

JsonParser::~JsonParser()
{
}

std::unique_ptr<AuthorInfo> JsonParser::parseAuthorInfo(const std::string& data)
{
	nlohmann::json json = nlohmann::json::parse(data);
	auto p = std::make_unique<AuthorInfo>();
	p->setAuthorName(json["author_name"]);
	p->setEmail(json["email"]);
	return p;
}
