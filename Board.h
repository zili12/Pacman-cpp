#ifndef _BOARD_H_
#define _BOARD_H_

#include "Point.h"

class Board {

public:
	char mati[25][80];
	// A flag to check if to set colored or non colored game
	static bool colored; 
	static vector<string> fileNamesList;
	static string singleScreenName;
	static int maxX;
	static int maxY;
	//static Point initialPacman;
	static Point info;
	static Point PacmanPos;
	static Point GhostsPos[4];
	static int ghostCount;
	static int pacmanCount;

	// Function that prints the board on the screen
	int print();
	// Get function to get a char from a given point 
	char getPoint(const Point& pos) const { return mati[pos.getY()][pos.getX()]; }
	// Set function to update a char in a given point
	void setPoint(const Point& pos, char updateChar) { mati[pos.getY()][pos.getX()] = updateChar; }

	int readScreens(string name);
	void getBoardSize(string name, ifstream& Map);
	void getLocations(ifstream& Map);
	void createFileList(vector<string> &fileNamesList);
	bool hasEnding(string fullString, string const& ending);

};

#endif