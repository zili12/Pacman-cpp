#include "GhostBest.h"



void GhostBest::move(const bool& isCrumb, const Point& pacmanPos, const Board& b)
{
	// The function erase the ghost from the cuurent position, 
	// change it's position to a random direction and draw it again there.

	setDirection(calculateNextBest(pacmanPos, b));
	Point next = nextPos(_pos, _direction);
	while (b.mati[next.getY()][next.getX()] == '#')
	{
		setDirection(calculateNextBest(pacmanPos, b));
		next = nextPos(_pos, _direction);
	}
	erase(isCrumb);
	step();
	setTextColor(_color);
	_pos.draw(_figure);
}