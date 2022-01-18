#ifndef _POINT_H_
#define _POINT_H_

#include "io_utils.h"
#include "Enum.h"

class Point {
	// The point coordinate
	int _x, _y;
public:
	// C'tor with default position
	Point(int x = 1, int y = 1) : _x(x), _y(y) {}
	// Const get functions to reach data members
	int getX() const { return _x; }
	int getY() const { return _y; }
	// Set function to update data in existing point
	void set(int x, int y) { _x = x; _y = y; }
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
	// Const function to print a char in a point
	void draw(char ch) const;
	// Function to mimic moving of a point to a given direction
	void movePacman(int direction);

	bool operator==(Point point) {
		if((_x==point.getX())&&(_y==point.getY()))
			return true;
		else
			return false;
	}

	// D'tor
	~Point() {}
};

#endif