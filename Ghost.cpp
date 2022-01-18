#include "Ghost.h"
#include "Board.h"
#include "ThePacmanGame.h"


void Ghost::erase(const bool& isCrumb)const
{
	// Function to draw whatever was in a position before the ghost visit: crumb or space
	if (isCrumb)
	{
		if (Board::colored) { setTextColor(Color::BROWN); }
		_pos.draw('.');
	}
	else
	{
		_pos.draw(' ');
	}
}

void Ghost::step() {
	// Checking cases according to the direction
	switch (_direction) {
	case UP: // UP
		_pos.setY(_pos.getY() - 1);
		if (_pos.getY() < 0) { _pos.setY(1); _direction = DOWN; }
		break;
	case DOWN: // DOWN
		_pos.setY(_pos.getY() + 1);
		if (_pos.getY() > Board::maxY - 1) { _pos.setY(Board::maxY - 2); _direction = UP; }
		break;
	case LEFT: // LEFT
		_pos.setX(_pos.getX() - 1);
		if (_pos.getX() < 1) { _pos.setX(2); _direction = RIGHT; }
		break;
	case RIGHT: // RIGHT
		_pos.setX(_pos.getX() + 1);
		if (_pos.getX() > Board::maxX - 1) { _pos.setX(Board::maxX - 1); _direction = LEFT; }
		break;
	case STAY: // STAY
		break;
	}
}

Point Ghost::nextPos(const Point& pos, const int& dir) const
{
	Point res;
	switch (dir) {
	case 0: // UP
		res.set(pos.getX(), pos.getY() - 1);
		break;
	case 1: // DOWN
		res.set(pos.getX(), pos.getY() + 1);
		break;
	case 2: // LEFT
		res.set(pos.getX() - 1, pos.getY());
		break;
	case 3: // RIGHT
		res.set(pos.getX() + 1, pos.getY());
		break;
	case 4: // STOP
		break;
	}
	return res;
}


int Ghost::checkMinimal(const double& pathUp, const double& pathRight, const double& pathDown, const double& pathLeft)const
{
	double min = pathUp;
	int dir = UP;
	if (min > pathRight)
	{
		min = pathRight;
		dir = RIGHT;
	}
	if (min > pathDown)
	{
		min = pathRight;
		dir = DOWN;
	}
	if (min > pathLeft)
	{
		min = pathRight;
		dir = LEFT;
	}
	return dir;
}

Point Ghost::calculateNext(const Point& pacmanPos)const
{
		return nextPos(getPos(), getDirection());
}

int Ghost::calculateNextBest(const Point & pacmanPos, const Board & b)const
{
	int pacmanX = pacmanPos.getX(), pacmanY = pacmanPos.getY();
	int ghostX = _pos.getX(), ghostY = _pos.getY();
	double pathUp = MAXPATH, pathRight = MAXPATH, pathDown = MAXPATH, pathLeft = MAXPATH;
	if (isValid(UP, b) && _direction != DOWN)
		pathUp = sqrt(pow(abs(pacmanX - ghostX), 2) + pow(abs(pacmanY - (ghostY - 1)), 2));
	if (isValid(RIGHT, b) && _direction != LEFT)
		pathRight = sqrt(pow(abs(pacmanX - (ghostX + 1)), 2) + pow((abs(pacmanY - ghostY)), 2));
	if (isValid(DOWN, b) && _direction != UP)
		pathDown = sqrt(pow(abs(pacmanX - ghostX), 2) + pow(abs(pacmanY - (ghostY + 1)), 2));
	if (isValid(LEFT, b) && _direction != RIGHT)
		pathLeft = sqrt(pow(abs(pacmanX - (ghostX - 1)), 2) + pow((abs(pacmanY - ghostY)), 2));
	int newDir = checkMinimal(pathUp, pathRight, pathDown, pathLeft);

	return newDir;
}

bool Ghost::isValid(const int& dir, const Board & b)const
{
	Point next = nextPos(_pos, dir);
	if (b.mati[next.getY()][next.getX()] == '#')
		return false;
	else
		return true;
}

void Ghost::simpleMove(const bool& isCrumb, const Point& pos, const Board& b)
{
	// The function erase the ghost from the cuurent position, 
	// change it's position to a random direction and draw it again there.
	Point next = calculateNext(pos);
	if (b.mati[next.getY()][next.getX()] == '#')
		return;

	erase(isCrumb);
	step();
	setTextColor(_color);
	_pos.draw(_figure);
}


