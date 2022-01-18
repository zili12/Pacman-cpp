#include "ThePacmanGame.h"
#include "ThePacmanGameSilent.h"
#include "io_utils.h"

void ThePacmanGameSilent::start() 
{
	Board::colored = true;
	runByScreens();
	clear_screen();
	if (finalTest)
	{
		setTextColor(Color::GREEN);
		cout << "The final Test has passed successfully";
	}
	else
	{
		setTextColor(Color::RED);
		cout << "The final Test has not passed successfully";
	}
	setTextColor(Color::WHITE);
}

void ThePacmanGameSilent::init() 
{
	lives = 3;
	score = 0;
	b.createFileList(Board::fileNamesList);
	
	return;
}

void ThePacmanGameSilent::run(string name)
{
	clear_screen();
	hideCursor();
	string stepsFileName, resultFileName;

	createNewfileNames(name, stepsFileName, resultFileName);
	ifstream stepsFile(stepsFileName);
	ifstream resultFile(resultFileName);

	char key = 0;
	char isActive = 0;
	char tmp;
	int dir = 0, x, y;
	int timeInGame = 1, timeInFile, timeInResultFile;
	bool wait = true, isCrumb = false, stop = false, test = true;

	GhostNovice gn0(UP, Board::GhostsPos[0]), gn1(DOWN, Board::GhostsPos[1]), gn2(UP, Board::GhostsPos[2]), gn3(DOWN, Board::GhostsPos[3]);
	Ghost* g[4];
	g[0] = &gn0; g[1] = &gn1; g[2] = &gn2; g[3] = &gn3;

	Pacman p(Point(Board::PacmanPos.getX(), Board::PacmanPos.getY()));
	Fruit f(Point(22, 13));
	Point next;

	if (Board::colored) { setColors(p, g, f); }
	while (!stepsFile.eof())
	{
		stepsFile >> timeInFile;
		stepsFile >> key;
		handlePacmanMove(p, key, dir, next);

		stepsFile >> isActive;
		f.setVisible(charToBool(isActive));

		if (f.getVisible())
		{
			f.setFigure('0');

			stepsFile >> x;
			stepsFile >> y;
			Point pos = f.setPos(x, y);
		}
		//Ghost Move
		stepsFile >> isActive;
		wait = charToBool(isActive);
		for (int i = 0; i < Board::ghostCount; i++)
		{
			stepsFile >> key;
			dir = charToDirection(key);
			g[i]->setDirection(dir);
		}
		ghostsMove(wait, stop, isCrumb, g, p);

		stepsFile >> key;
		dir = charToDirection(key);
		f.setDirection(dir);
		if (f.getVisible())
		{
			fruitsMove(wait, stop, isCrumb, f, p);
		}

		//check Fruit VS Pacman
		pacmanVsFruit(p, f);
		//check Ghost VS Pacman
		pacmanVsGhosts(p, g, name);
		if (pacmanDied)
		{
			resultFile >> timeInFile;
			if (timeInFile != timeInGame)
				test = false;
			// initializing positions
			pacmanDied = false;
			p.setPos(Board::PacmanPos);
			p.setDirection(STAY);
			for (int i = 0; i < Board::ghostCount; i++)
			{
				g[i]->setPos(Board::GhostsPos[i]);
				if (i % 2 == 0)
					g[i]->setDirection(UP);
				else
					g[i]->setDirection(DOWN);
			}
		}
		timeInGame++;
	}
	if (remainedCrumbs <= 0)
	{
		resultFile >> timeInFile;
		if (timeInFile != (timeInGame-2))
			test = false;
	}

	stepsFile.close();
	resultFile.close();
	clear_screen();
	if (test)
	{
		setTextColor(Color::GREEN);
		cout << "The Test of " << name << " has passed successfully";
	}
	else
	{
		setTextColor(Color::RED);
		cout << "The Test of " << name << " has not passed successfully";
	}
	Sleep(1500);
	if (!test)
		finalTest = false;
}

int ThePacmanGameSilent::charToDirection(const char& tmp)
{
	switch (tmp)
	{
	case 'U':
		return UP;
	case 'D':
		return DOWN;
	case 'L':
		return LEFT;
	case 'R':
		return RIGHT;
	case 'S':
		return STAY;
	default:
		return NULL; 
	}
}

bool ThePacmanGameSilent::charToBool(const char& tmp)
{
	if (tmp == 'Y')
		return true;
	else // tmp== 'N'
		return false;
}

void ThePacmanGameSilent::runByScreens()
{
	init();
	for (int i = 0; i < Board::fileNamesList.size(); i++)
	{
		remainedCrumbs = b.readScreens(Board::fileNamesList[i]) -1;
		//remainedCrumbs = 40;
		if (!isBoardValid())
		{
			wannaPlay = false;
			return;
		}
		run(Board::fileNamesList[i]);
		if (!lives)
		{
			wannaPlay = false;
			return;
		}
		Board::pacmanCount = 0; Board::ghostCount = 0;
	}
	return;
}

void ThePacmanGameSilent::pacmanVsGhosts(Pacman& p, Ghost* g[], string name)
{
	for (int i = 0; i < 4; i++)
	{
		if (p.getPos() == g[i]->getPos())
		{
			pacmanDied = true;
			ThePacmanGame::lives--;
			return;
		}
	}
}

void ThePacmanGameSilent::ghostsMove(bool& wait, bool& stop, bool& isCrumb, Ghost* g[], Pacman& p)
{
	Point next;
	if ((!wait) && (!stop))
	{
		for (int i = 0; i < Board::ghostCount; i++)
		{
			isCrumb = (isBreadCrumb(g[i]->getPos()));
			next = nextPos(g[i]->getPos(), g[i]->getDirection());
			if (b.mati[next.getY()][next.getX()] == '#')
				return;

			g[i]->step();
			ghostsVsGhost(i, g);
		}
		wait = true;
	}
	else
		wait = false;
}

void ThePacmanGameSilent::handlePacmanMove(Pacman& p, char& key, int& dir, Point& next)
{
	//Pacman move
	directionToKey(key);
	dir = p.changeDirection(key);
	p.setDirection(dir);

	//check wall
	next = nextPos(p.getPos(), p.getDirection());
	if (b.getPoint(next) == '#')
		p.setDirection(STAY);
	else
		p.step();

	// check crumb for pacman
	if (b.getPoint(p.getPos()) == '.')
	{
		b.setPoint(p.getPos(), '%');
		score++;
		remainedCrumbs--;
	}
	return;
}

void ThePacmanGameSilent::directionToKey(char& key)
{
	switch (key)
	{
	case 'U':
		key = 'w';
		break;
	case 'D':
		key = 'x';
		break;
	case 'L':
		key = 'a';
		break;
	case 'R':
		key = 'd';
		break;
	case 'S':
		key = 's';
		break;
	default:
		break;
	}
}

void ThePacmanGameSilent::fruitsMove(bool& wait, bool& stop, bool& isCrumb, Fruit& f, Pacman& p)
{
	Point next;

	if ((!wait) && (!stop))
	{
		isCrumb = (isBreadCrumb(f.getPos()));
		next = nextPos(f.getPos(), f.getDirection());

		if (b.getPoint(next) == '#')
		{
			f.erase(isCrumb);
			return;
		}
		f.step();
	}
}

void ThePacmanGameSilent::pacmanVsFruit(Pacman& p, Fruit& f)
{
	// Checking if pacman has the same location as the fruit
	if (p.getPos() == f.getPos())
	{
		score += f.getFigure() - 48;
		f.changeVisible();
	}
}

