#ifndef _PACMAN_H_
#define _PACMAN_H_

#include "Creature.h"

class Pacman : public Creature {
	// Keys to move
	static constexpr char _arrowKeys[5] = { 'w','x','a','d','s' };
public:
	// C'tor
	Pacman(Point pos = Point(42, 1), Color c = Color::WHITE, char figure = 'C') : Creature(pos, c, figure) {}
	void setPos(Point& pos) { _pos.setX(pos.getX()); _pos.setY(pos.getY());	}
	// Const get functions to reach data members
	const Point& getPos() const { return _pos; }

	// Function to move pacman
	void move(bool isCrumb=true);
	void step();
	void loseLife(bool colored);
	// Function to change the direction according to player choice
	int changeDirection(char key);
	// Functions to make both lower and upper case letter work
	bool isCapital(char key);
	void changeToLower(char& key);
};

#endif