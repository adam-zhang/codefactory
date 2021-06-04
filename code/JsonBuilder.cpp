/********************************************************************************
> FileName:	JsonBuilder.cpp
> Author:	Mingping Zhang
> Email:	mingpingzhang@163.com
> Create Time:	Fri Jun 04 11:09:51 2021
********************************************************************************/

#include "JsonBuilder.h"
#include "nlohmann/json.hpp"
#include "AuthorInfo.h"

JsonBuilder::JsonBuilder()
{
}

JsonBuilder::~JsonBuilder()
{
}

std::string JsonBuilder::build(const std::shared_ptr<AuthorInfo>& p)
{
	nlohmann::json json;
	json["author_name"] = p->authorName();
	json["email"] = p->email();
	return json.dump();
}
