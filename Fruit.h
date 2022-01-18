#ifndef _FRUIT_H_
#define _FRUIT_H_

#include "Creature.h"

#define MAXVALUE 9
#define MINVALUE 5

class Fruit : public Creature {
	// Data members
	bool _visible = false;
public:
	// C'tor
	//Fruit(Point pos = Point(25, 13), Color c = Color::WHITE, char figure = 'A') :
	Fruit(Point pos = (25,14), char figure = 'C', Color c = Color::WHITE, int dir = UP) :
		Creature(pos, c, figure, dir) {}

	bool getVisible()const{ return _visible; }
	void setVisible(const bool& visible) { _visible = visible; }
	void changeVisible() {if (_visible)_visible = false; else _visible = true;}

	void setPosition(const Point& pos) { _pos = pos; }

	char getFigure() { return _figure; }

	
	void randValue();
	Point randPosition();

	// Function to move a ghost
	void move(bool isCrumb);

	// Function to make sure ghosts dont eat crumbs
	void erase(bool isCrumb);

	void step();
};

#endif