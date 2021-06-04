/********************************************************************************
> FileName:	AuthorInfo.h
> Author:	Mingping Zhang
> Email:	mingpingzhang@163.com
> Create Time:	Fri Jun 04 10:47:58 2021
********************************************************************************/
#ifndef AUTHORINFO_H
#define AUTHORINFO_H

#include <string>
#include "Properties.h"

class AuthorInfo
{
public:
	AuthorInfo();
	~AuthorInfo();
	
	PROPERTY(std::string, authorName, setAuthorName)
	PROPERTY(std::string, email, setEmail)
};
#endif//AUTHORINFO_H
