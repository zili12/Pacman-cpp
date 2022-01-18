#ifndef _ENUM_H_
#define _ENUM_H_

enum Color{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHTGREY = 7,
	DARKGREY = 8,
	LIGHTBLUE = 9,
	LIGHTGREEN = 10,
	LIGHTCYAN = 11,
	LIGHTRED = 12,
	LIGHTMAGENTA = 13,
	YELLOW = 14,
	WHITE = 15
};

enum { ESC = 27 };

enum Direction{
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3,
	STAY = 4
};

enum Level{
	NOVICE = 1,
	GOOD = 2,
	BEST = 3
};

enum Screens{
	NONE = 0,
	MULTIPLE = 1,
	SINGLE = 2
};

enum Mode{
	SAVE = 1,
	LOAD = 2,
	SILENT =3
};

enum Choice{
	START = '1',
	STARTWOC = '2',
	INSTRUCTIONS = '8',
	EXIT = '9'
};

enum Print {
	WALL = '#',
	BREAD = '.',
	SPACE = '%',
	GHOST = '$'
};



//enum Walls {|, +, -, #};

#endif