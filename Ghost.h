#ifndef _GHOST_H_
#define _GHOST_H_
#define MAXPATH 1000

#include "Board.h"
#include "Creature.h"

class Ghost : public Creature {
public:
	// C'tor
	Ghost(Point pos = Point(25,13), int dir = UP, Color c = Color::WHITE, char figure = 'A') : Creature(pos,c,figure,dir) {}

	// Function to move a ghost
	virtual void move(const bool& isCrumb, const Point& pacmanPos, const Board& b) = 0;
	void setPos(Point& pos) { _pos.setX(pos.getX()); _pos.setY(pos.getY()); }
	void erase(const bool& isCrumb)const;
	void step();
	void simpleMove(const bool& isCrumb, const Point& pacmanPos, const Board& b);

protected:
	int checkMinimal(const double& pathUp, const double& pathRight, const double& pathDown, const double& pathLeft)const;
	Point nextPos(const Point& pos, const int& dir) const;
	int calculateNextBest(const Point& pacmanPos, const Board& b)const;
	bool isValid(const int& dir, const Board& b)const;
	// Function to make sure ghosts dont eat crumbs
	Point calculateNext(const Point& pacmanPos)const;
};

#endif