#pragma once
#include <exception>
class BoardNotSupportedExeption :public std::exception
{
	virtual const char* what() const throw() {
		return "Board is not supported";
	}

};
