#include "Fruit.h"
#include "Board.h"
#include "ThePacmanGame.h"

void Fruit::move(bool isCrumb)
{
	// The function erase the ghost from the cuurent position, 
	// change it's position to a random direction and draw it again there.
	erase(isCrumb);
	step();
	setTextColor(_color);
	_pos.draw(_figure);
}

void Fruit::step(){
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
		if (_pos.getX() > Board::maxX) { _pos.setX(Board::maxX - 1); _direction = LEFT; }
		break;
	case STAY: // STAY
		_pos.setX(_pos.getX());
		_pos.setY(_pos.getY());
		break;
	}
}

void Fruit::erase(bool isCrumb)
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


void Fruit::randValue()
{
	int figure= (rand() % (MAXVALUE - MINVALUE + 1) + MINVALUE);  
	//_figure = figure - '0';
	_figure = figure + 48;
}

Point Fruit:: randPosition()
{
	int x = rand() % (Board::maxX);
	int y = rand() % (Board::maxY); 
	return Point(x, y);
}


