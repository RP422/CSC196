// Use includes closest to farthest

#include "assert.h"
#include <iostream>

void _assert(bool expression, const char * expression_string, const char * filename, int line, const char * function_name)
{
	if (!expression)
	{
		std::cout << std::endl;
		std::cout << "Assertion Failed: " << expression_string << std::endl;
		std::cout << "Source: " << filename << std::endl;
		std::cout << "Function: " << function_name << std::endl;
		std::cout << "Line: " << line << std::endl;
		std::cout << std::endl;
		
		abort();
	}
}

void _assert(bool expression, const char * expression_string, const char * filename, int line, const char * function_name, const char * message)
{
	if (!expression)
	{
		std::cout << std::endl;
		std::cout << "Assertion Failed: " << expression_string << std::endl;
		std::cout << message << std::endl;
		std::cout << "Source: " << filename << std::endl;
		std::cout << "Function: " << function_name << std::endl;
		std::cout << "Line: " << line << std::endl;
		std::cout << std::endl;

		abort();
	}
}
