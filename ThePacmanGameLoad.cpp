#include "ThePacmanGame.h"
#include "ThePacmanGameLoad.h"
#include "io_utils.h"

void ThePacmanGameLoad::start()
{
	Board::colored = true;
	runByScreens();
}

void ThePacmanGameLoad::init()
{
	lives = 3;
	score = 0;
	b.createFileList(Board::fileNamesList);	
	return;
}

void ThePacmanGameLoad::run(string name)
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
	int timeInGame = 1, timeInFile;
	bool wait = true, isCrumb = false, stop = false, test = true;

	GhostNovice gn0(UP, Board::GhostsPos[0]), gn1(DOWN, Board::GhostsPos[1]), gn2(UP, Board::GhostsPos[2]), gn3(DOWN, Board::GhostsPos[3]);
	Ghost* g[4];
	g[0] = &gn0; g[1] = &gn1; g[2] = &gn2; g[3] = &gn3;

	Pacman p(Point(Board::PacmanPos.getX(), Board::PacmanPos.getY()));
	Fruit f(Point(22, 13));
	Point next;

	// Print board, score and lives
	remainedCrumbs = b.print() - 1;
	//remainedCrumbs = 40;

	gotoxy(41, 24);
	printScore();
	printLives();

	if (Board::colored) { setColors(p, g, f); }
	while (!stepsFile.eof())
	{
		stepsFile >> timeInFile;
		//gotoxy(60, 1);
		//cout << timeInGame; //possible to delete only for debug

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
				g[i]->erase(isCrumb);
				g[i]->setPos(Board::GhostsPos[i]);
				if (i % 2 == 0)
					g[i]->setDirection(UP);
				else
					g[i]->setDirection(DOWN);
			}
		}
		//Sleep(1);
		timeInGame++;
	}
	if (remainedCrumbs  <= 0)
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
	setTextColor(Color::WHITE);
	Sleep(2000);
}

int ThePacmanGameLoad::charToDirection(const char& tmp)
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

bool ThePacmanGameLoad::charToBool(const char& tmp)
{
	if (tmp == 'Y')
		return true;
	else // tmp== 'N'
		return false;
}

void ThePacmanGameLoad::runByScreens()
{
	init();
	for (int i = 0; i < Board::fileNamesList.size(); i++)
	{
		printLevel(i);
		b.readScreens(Board::fileNamesList[i]);
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

void ThePacmanGameLoad::pacmanVsGhosts(Pacman& p, Ghost* g[], string name)
{
	for (int i = 0; i < 4; i++)
	{
		if (p.getPos() == g[i]->getPos())
		{
			pacmanDied = true;
			ThePacmanGame::lives--;
			if (lives)
				p.loseLife(Board::colored);

			Sleep(200);
			return;
		}
	}
}

void ThePacmanGameLoad::ghostsMove(bool& wait, bool& stop, bool& isCrumb, Ghost* g[], Pacman& p)
{
	Point next;
	if ((!wait) && (!stop))
	{
		for (int i = 0; i < Board::ghostCount; i++)
		{
			isCrumb = (isBreadCrumb(g[i]->getPos()));
			g[i]->simpleMove(isCrumb, g[i]->getPos(), b);
			ghostsVsGhost(i, g);
		}
		wait = true;
	}
	else
		wait = false;
}

void ThePacmanGameLoad::fruitsMove(bool& wait, bool& stop, bool& isCrumb, Fruit& f, Pacman& p)
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
		f.move(isCrumb);
	}
}

void ThePacmanGameLoad::handlePacmanMove(Pacman& p, char& key, int& dir, Point& next)
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
		p.move();

	//check crumb for pacman
	if (b.getPoint(p.getPos()) == '.')
	{
		b.setPoint(p.getPos(), '%');
		score++;
		remainedCrumbs--;
		printScore();
	}
	return;
}

void ThePacmanGameLoad::directionToKey(char& key)
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
