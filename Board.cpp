#include "io_utils.h"
#include "Board.h"
#include "ThePacmanGame.h"
#include <filesystem>

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
using std::filesystem::directory_iterator;
using std::filesystem::current_path;
//
bool Board::colored = true;
int Board::maxX = 0;
int Board::maxY = 0;
vector<string> Board::fileNamesList;
string Board::singleScreenName;
Point Board::info(1,1);
Point Board::PacmanPos(1, 1);
Point Board::GhostsPos[4];
int Board::ghostCount = 0;
int Board::pacmanCount = 0;

int Board::print()
{
	int count = 0;
	// A loop function that prints the matrix of the board
	for (int y = 0; y < maxY; y++) {
		for (int x = 0; x < maxX; x++) {
			switch (mati[y][x])
			{
			case WALL:
				if (Board::colored) { setTextColor(Color::LIGHTBLUE); }
				cout << '#';
				break;
			case SPACE:
			case GHOST:
				cout << ' ';
				break;
			case BREAD:
				if (Board::colored) {setTextColor(Color::BROWN);}
				cout << '.';
				count++;
				break;
			default:
				cout << mati[y][x];
				break;
			}
		}
		cout << std::endl;
	}
	return count;
}

int Board::readScreens(string name)
{	
	char temp;
	string Line;
	int i = 0, j = 0;
	int countCrumbs = 0;
	bool infoFound = false;
	ifstream Map(name);
	getBoardSize(name, Map);
	getLocations(Map);
	
	if (Map.is_open())
	{
		Map.clear();
		Map.seekg(0);
		for (i; i < maxY; i++)
		{
			(getline(Map, Line));
			for (j; j < Line.length(); j++)
			{
			//	Map.get(temp);

				temp = Line[j];
				if ((temp=='#') || (temp=='%') || (temp == '$'))
					mati[i][j] = temp;
				else if (temp == ' ')
				{
					mati[i][j] = '.';
					countCrumbs++;
				}
				if ((temp == '&') || (temp == '@'))
					mati[i][j] = ' ';
			}
			//if (!infoFound)
				//Map.seekg((i+1)*j
			j = 0;
		}
		Map.close();
	}
	else {
		clear_screen();
		cout << "Unable to open";
		Sleep(500);
	}
	
	return countCrumbs;
}

void Board::getBoardSize(string name, ifstream &Map)
{
	string Line;
	(getline(Map, Line));
	maxX = (int)Line.length();
	Map.seekg(0, std::ios_base::end);
	maxY = (((int)Map.tellg()-1) / maxX)-1;
}

void Board::getLocations(ifstream& Map)
{
	int i, j=0;
	bool found = false;
	string Line;
	//info location
	Map.seekg(0);
	int legendX, legendY;
	while (!found)
	{
		for (i = 0; i < maxY+1; i++)
		{
			(getline(Map, Line));
			for (j = 0; j < Line.length(); j++)
				if (Line[j] == '&')
				{
					found = true;
					legendX = j;
					legendY = i;
				}
		}
	}

	info.setX(legendX); info.setY(legendY);

	//pacman location
	found = false;
	Map.clear();
	Map.seekg(0);
	int pacmanX, pacmanY;
	while (!found)
	{
		for (i = 0; i < maxY + 1; i++)
		{
			(getline(Map, Line));
			for (j = 0; j < Line.length(); j++)
				if (Line[j] == '@')
				{
					found = true;
					pacmanX = j;
					pacmanY = i;
					pacmanCount++;
				}
		}
	}
	PacmanPos.setX(pacmanX); PacmanPos.setY(pacmanY);

	//ghost location
	Map.clear();
	Map.seekg(0);
	int ghostX, ghostY;
	while (!Map.eof())
	{
		for (i = 0; i < maxY + 1; i++)
		{
			(getline(Map, Line));
			for (j = 0; j < Line.length(); j++)
				if (Line[j] == '$')
				{
					ghostX = j;
					ghostY = i;
					GhostsPos[ghostCount]= (Point(ghostX, ghostY));
					ghostCount++;
				}
		}
	}
}

void Board::createFileList(vector<string> &fileNamesList)
{
	for (const auto& file : directory_iterator(current_path()))
	{
		filesystem::path p = file.path();
		string s = p.string();
		if (hasEnding(s, ".screen.txt"))
		{
			string delimiter = "pacman_";
			string fileName = s.substr(s.find(delimiter), s.length());
			fileNamesList.push_back(fileName);
		}
	}
}

bool Board::hasEnding(string fullString, string const& ending) {
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else {
		return false;
	}
}