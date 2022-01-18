#ifndef _GHOSTGOOD_H_
#define _GHOSTGOOD_H_

#include "Ghost.h"

class GhostGood : public Ghost/*, public GhostBest, public GhostNovice*/ {
public:
	// C'tor
	GhostGood(int dir, Point pos = Point(25, 13)) : Ghost(pos, dir) {}

	// Function to move a ghost
	void move(const bool& isCrumb, const Point& pacmanPos, const Board& b) override;

protected:
	//int calculateNextGood(const Point& pacmanPos, const Board& b);
	//bool isValid(int dir, const Board& b);

};

#endif