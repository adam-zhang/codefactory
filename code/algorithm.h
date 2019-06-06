#ifndef __ALGORITHM__H
#define __ALGORITHM__H

#include <string>
#include <cctype>

template<typename T>
std::basic_string<T> toUpper(const std::basic_string<T>& value)
{
	std::basic_string<T> o;
	for(auto c = value.begin(); c != value.end(); ++c)
	{
		int i = *c;
		int r = std::toupper(i);
		o.push_back((T)r);
	}
	return o;
}

template<typename T>
std::basic_string<T> toLower(const std::basic_string<T>& value)
{
	std::basic_string<T> s;
	for(auto c : value)
	{
		int r = std::tolower((int)c);
		o.push_back((T)r);
	}
	return s;
}
#endif//__ALGORITHM__H
