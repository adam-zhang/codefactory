#ifndef __LOGGER__H
#define __LOGGER__H

#include <string>
#include <sstream>

class Logger
{
	private:
		Logger();
		~Logger();
	public:
		static void output(const std::string&);

		template<typename T>
		static void output(const std::string& note, const T& value)
		{
			std::stringstream ss;
			ss << note << ":" << value;
			output(ss.str());
		}
};
#endif//__LOGGER__H
