#pragma once
#include <exception>
class NoBoardsException :public std::exception
{
public:
	virtual const char* what() const throw() {
		return "Sorry, there are no game boards in the directory";
	}

};