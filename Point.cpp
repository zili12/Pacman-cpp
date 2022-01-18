#include "Point.h"
#include "Board.h"


void Point::draw(char ch) const {
	// Set cursor to wanted coordinate and print
	gotoxy(_x, _y);
	cout << ch << endl;
}

void Point::movePacman(int dir) {
	// Checking cases according to the direction
	// this is Or
	switch (dir) {
	case UP: // UP
		--_y;
		if (_y < 0) {_y = Board::maxY-1;}
		break;
	case DOWN: // DOWN
		++_y;
		if (_y > Board::maxY-1) {_y = 0;}
		break;
	case LEFT: // LEFT
		//--_x;
		--_x;
		if (_x < 1) {_x = Board::maxX-1;}
		break;
	case RIGHT: // RIGHT
		//++_x;
		++_x;
		if (_x > Board::maxX-1) {_x = 0;}
		break;
	case STAY: // STAY
		_x = _x;
		_y = _y;
		break;
	}
}
