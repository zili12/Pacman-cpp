#ifndef _GHOSTNOVICE_H_
#define _GHOSTNOVICE_H_

#include "Ghost.h"

class GhostNovice : public Ghost {
public:
	// C'tor
	GhostNovice(int dir, Point pos = Point(25, 13)) : Ghost(pos, dir) {}

	// Function to move a ghost
	void move(const bool& isCrumb, const Point& pacmanPos, const Board& b) override;
	//void simpleMove(const bool& isCrumb, const Point& pacmanPos, const Board& b);



};

#endif