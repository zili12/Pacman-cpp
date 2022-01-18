#ifndef _CREATURE_H_
#define _CREATURE_H_

#include "Point.h"

class Creature {
protected: // Data members
	Point _pos;
	Color _color;
	char _figure;
	int _direction;
public:
	// C'tor
	Creature(Point pos = Point(0, 0), Color c = Color::WHITE, char figure = '?', int dir = STAY) :
		_pos(pos), _color(c), _figure(figure), _direction(dir) {}
	// Const get functions to reach data members
	Point getPos() const { return _pos; }
	int getDirection() const { return _direction; }
	// Set function to update data in existing ghost
	Point setPos(int x, int y) { _pos.set(x, y); return _pos; }
	void setColor(Color c) { _color = c; }
	void setFigure(const char c) { _figure = c; }
	void setDirection(int dir) { _direction = dir; }
	// Function to move a creature
	//virtual void move(bool isCrumb) = 0;
};

#endif