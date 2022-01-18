#include "GhostGood.h"
#include "GhostBest.h"
#include "GhostNovice.h"


void GhostGood::move(const bool& isCrumb, const Point& pacmanPos, const Board& b)
{
	static bool isSmart = true;
	static int count = 0;

	if (!isSmart) //isSmart is false and he need to move novice for 5 moves
	{
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

		if (count == 5)
		{
			isSmart = true;
			count = 0;
		}
		else
			count++;
	}
	else
		if (rand() % 20 == 1)// randomally once in 20
			isSmart = false;


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
