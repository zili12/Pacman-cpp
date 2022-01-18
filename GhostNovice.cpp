#include "GhostNovice.h"
#include "InputParser.h"

void GhostNovice::move(const bool& isCrumb, const Point& pacmanPos, const Board& b)
{
	// The function erase the ghost from the cuurent position, 
	// change it's position to a random direction and draw it again there.
	Point next = calculateNext(pacmanPos);
	while (b.mati[next.getY()][next.getX()] == '#')
	{
		setDirection(rand() % 4); // Stupid
		next = calculateNext(pacmanPos);
	}

	erase(isCrumb);
	step();
	setTextColor(_color);
	_pos.draw(_figure);
}





