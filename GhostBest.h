#ifndef _GHOSTBEST_H_
#define _GHOSTBEST_H_

#include "Ghost.h"

class GhostBest : public Ghost {
public:
	// C'tor
	GhostBest(int dir, Point pos = Point(25, 13)) : Ghost(pos, dir) {}

	// Function to move a ghost
	void move(const bool& isCrumb, const Point& pacmanPos, const Board& b) override;

protected:
	//int calculateNextBest(const Point& pacmanPos, const Board& b);
	//bool isValid(int dir, const Board& b);

};

#endif