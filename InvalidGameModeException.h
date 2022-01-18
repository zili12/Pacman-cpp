#pragma once
#include <exception>
class InvalidGameModeException : public exception
{
public: 
	const char* what() const throw()override {
		return "Invalid game mode";
	}

};
