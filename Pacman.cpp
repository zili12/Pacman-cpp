#include "Point.h"
#include "Pacman.h"
#include "Enum.h"
#include "Board.h"

void Pacman::move(bool isCrumb)
{
	// The function erase pacman from the cuurent position, 
	// change it's position to the chosen direction and draw it again there.
	_pos.draw(' ');
	step();
	setTextColor(_color);
	_pos.draw(_figure);
}

void Pacman::step() {
	// Checking cases according to the direction
	switch (_direction) {
	case UP: // UP
		_pos.setY(_pos.getY() - 1);
		if (_pos.getY() < 0) { _pos.setY(Board::maxY - 1);  }
		break;
	case DOWN: // DOWN
		_pos.setY(_pos.getY() + 1);
		if (_pos.getY() > Board::maxY - 1) { _pos.setY(0); }
		break;
	case LEFT: // LEFT
		//--_x;
		_pos.setX(_pos.getX() - 1);
		if (_pos.getX() < 1) { _pos.setX(Board::maxX - 1); }
		break;
	case RIGHT: // RIGHT
		//++_x;
		_pos.setX(_pos.getX() + 1);
		if (_pos.getX() > Board::maxX - 1) { _pos.setX(0); }
		break;
	case STAY: // STAY
		break;
	}
}


int Pacman::changeDirection(char key)
{
	// Firstly we check if it's lower or upper case and changing to lower if needed
	if (isCapital(key))
		changeToLower(key);
	switch (key) {
	case 'w': // UP
		return UP;
	case 'x': // DOWN
		return DOWN;
	case 'a': // LEFT
		return LEFT;
	case 'd': // RIGHT
		return RIGHT;
	case 's': // STAY
		return STAY;
	default:
		return _direction;
	}
}

bool Pacman::isCapital(char key)
{
	// Function that checks if a letter is upper case
	if ((key > 'A') && (key < 'Z'))
		return true;
	else
		return false;
}

void Pacman::changeToLower(char& key)
{
	// Function that changes upper case letters to lower case
	switch (key)
	{
	case 'W':
		key = 'w';
	break;
	case 'A':
		key = 'a';
		break;
	case 'D':
		key = 'd';
		break;
	case 'X':
		key = 'x';
		break;
	case 'S':
		key = 's';
		break;
	}
}

void Pacman::loseLife(bool colored)
{
	for (int i = 0; i < 4; i++)
	{
		gotoxy(_pos.getX(), _pos.getY());

		cout << " ";
		Sleep(200);
		gotoxy(_pos.getX(), _pos.getY());
		if (colored) { setTextColor(Color::RED); }
		cout << "C";
		Sleep(200);
	}
}