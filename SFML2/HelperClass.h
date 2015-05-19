#pragma once

#include <iostream>
#include <sstream>
#include <string>

class HelperClass
{
public:
	HelperClass(void);
	~HelperClass(void);

	static std::string IntToString(int d)
	{
	   std::stringstream ss;
	   ss << d;
	   return ss.str();
	}
};

