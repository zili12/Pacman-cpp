#include "ThePacmanGame.h"
#include "io_utils.h"

void ThePacmanGame::start()
{
	printMenu();
	checkChoice();
}

void ThePacmanGame::init()
{

	lives = 3;
	score = 0;
	if (screens == MULTIPLE)
	{
		b.createFileList(Board::fileNamesList);
	}
	else if (screens == SINGLE)
	{
		gotoxy(8, 9);
		if (Board::colored) { setTextColor(Color::WHITE); }
		cout << "Enter screen name:           "<<endl;
		gotoxy(8, 10);
		cout << "                        ";
		gotoxy(8, 10);
		cin >> Board::singleScreenName;
	}
}

void ThePacmanGame::checkBoardExist()
{
	if (!Board::fileNamesList.size())
		throw NoBoardsException();
}

void ThePacmanGame::run(string name)
{
	clear_screen();
	hideCursor();

	char key = 0;
	int dir = 0;
	bool wait = true, isCrumb = false, stop = false, died = false;

	GhostBest gb0(UP ,Board::GhostsPos[0]), gb1(DOWN, Board::GhostsPos[1]), gb2(UP, Board::GhostsPos[2]), gb3(DOWN, Board::GhostsPos[3]);
	GhostGood gg0(UP, Board::GhostsPos[0]), gg1(DOWN, Board::GhostsPos[1]), gg2(UP, Board::GhostsPos[2]), gg3(DOWN, Board::GhostsPos[3]);
	GhostNovice gn0(UP, Board::GhostsPos[0]), gn1(DOWN, Board::GhostsPos[1]), gn2(UP, Board::GhostsPos[2]), gn3(DOWN, Board::GhostsPos[3]);

	Ghost* g[4];

	if (ghostLevel == NOVICE)
	{
		g[0] = &gn0; g[1] = &gn1; g[2] = &gn2; g[3] = &gn3;
	}
	else if(ghostLevel == GOOD)
	{
		g[0] = &gg0; g[1] = &gg1; g[2] = &gg2; g[3] = &gg3;
	}
	else // BEST
	{
		g[0] = &gb0; g[1] = &gb1; g[2] = &gb2; g[3] = &gb3;
	}
	
	Pacman p(Point(Board::PacmanPos.getX(),Board::PacmanPos.getY()));
	Fruit f(Point(22,13));
	Point next;

	// Print board, score and lives
	remainedCrumbs = b.print() - 1;
	//remainedCrumbs = 40;

	gotoxy(41, 24);
	
	printScore();
	printLives();

	if (Board::colored) { setColors(p, g, f); }
	while ((lives != 0) && (remainedCrumbs != 0))
	{
		if (stop)
		{
			printPause();
			stop = false;
			key = _getch();
			if (key != ESC)
			{
				printContinue();
				stop = false;
				continue;
			}
			else
			{
				printGoodBye();
				return;
			}
		}

		if (key == ESC)
		{
			int dir = p.getDirection();
			stop = true;
			continue;
		}

		handlePacmanMove(p, key, dir, next);

		handleFruitActivity(f);

		//Ghost Move
		ghostsMove(wait, stop, isCrumb, g, p);
		if(f.getVisible())
			fruitsMove(wait, stop, isCrumb, f, p);
		
		//check Fruit VS Pacman
		pacmanVsFruit(p, f);
		//check Ghost VS Pacman
		pacmanVsGhosts(p, g, name);
		if (pacmanDied)
		{
			// initializing positions
			pacmanDied = false;
			p.setPos(Board::PacmanPos);
			p.setDirection(STAY);
			for (int i = 0; i < Board::ghostCount; i++)
			{
				g[i]->erase(isCrumb);
				g[i]->setPos(Board::GhostsPos[i]);
				if (i%2==0)
					g[i]->setDirection(UP);
				else
					g[i]->setDirection(DOWN);
			}
			printLives();
		}
		Sleep(200);
	}
}

void ThePacmanGame::printMenu() const
{
	clear_screen();
	printFrame();
	gotoxy(7, 9);
	if (Board::colored) { setTextColor(Color::GREEN); }
	cout << "(1) ";
	if (Board::colored) { setTextColor(Color::WHITE); }
	cout << "Start a new game with colors";
	gotoxy(7, 10);
	if (Board::colored) { setTextColor(Color::GREEN); }
	cout << "(2) ";
	if (Board::colored) { setTextColor(Color::WHITE); }
	cout << "Start a new game without colors";
	gotoxy(7, 11);
	if (Board::colored) { setTextColor(Color::GREEN); }
	cout << "(8) ";
	if (Board::colored) { setTextColor(Color::WHITE); }
	cout << "Present instructions and keys";
	gotoxy(7, 12);
	if (Board::colored) { setTextColor(Color::GREEN); }
	cout << "(9) ";
	if (Board::colored) { setTextColor(Color::WHITE); }
	cout << "EXIT";

	gotoxy(1, 24);
	setTextColor(WHITE);
}

void ThePacmanGame::printFrame() const
{
	char menu[24][50] = {
				 "+-------------------+ . | . +-------------------+",
				 "| . . . . . . . . . . . | . . . . . . . . . . . |",
				 "| . +-----+ . +-----+ . | . +-----+ . +-----+ . |",
				 "| . |     | . |     | . | . |     | . |     | . |",
				 "| . |     | . |     | . | . |     | . |     | . |",
				 "| . +-----+ . +-----+ . . . +-----+ . +-----+ . |",
				 "| . . . . . . . . # P A C M A N # . . . . . . . |",
				 "| .  _______________________________________  . |",
				 "| . |                                       | . |",
				 "| . |                                       | . |",
				 "+---|                                       |---+",
				 "    |                                       |    ",
				 "+---|                                       |---+",
				 "  . |_______________________________________| .  ",
				 "| .                                           . |",
				 "+---------+ . +   +-----+-----+   + . +---------+",
				 "| . . . . . . . . . . . | . . . . . . . . . . . |",
				 "| . ------+ . ------- . + . ------- . +------ . |",
				 "| . . . . | . . . . . . . . . . . . . | . . . . |",
				 "+------ . | . | . ------------- . | . | . ------+",
				 "| . . . . . . | . . . . . . . . . | . . . . . . |",
				 "| . ----------------- . | . ----------------- . |",
				 "| . . . . . . . . . . . | . . . . . . . . . . . |",
				 "+-------------------- . | . --------------------+" };
	for (int y = 0; y < 24; y++) {
		for (int x = 0; x < 50; x++) {
			switch (menu[y][x])
			{
			case '|':
			case '+':
			case '-':
			case '_':
				if (Board::colored) { setTextColor(Color::LIGHTBLUE); }
				break;
			case '#':
				if (Board::colored) { setTextColor(Color::YELLOW); }
				break;
			case '.':
				if (Board::colored) { setTextColor(Color::BROWN); }
				break;
			case '(':
				if (Board::colored) { setTextColor(Color::GREEN); }
				break;
			case 'P':
				if (Board::colored) { setTextColor(Color::WHITE); }
				break;
			default:
				break;
			}
			cout << menu[y][x];
		}
		cout << std::endl;
	}

	gotoxy(1, 24);
	setTextColor(WHITE);
}

void ThePacmanGame::printInstructions()
{
	clear_screen();
	gotoxy(20, 7);
	cout << "LEFT    a or A" << endl;
	gotoxy(20, 8);
	cout << "RIGHT   d or D" << endl;
	gotoxy(20, 9);
	cout << "UP      w or W" << endl;
	gotoxy(20, 10);
	cout << "DOWN    x or X" << endl;
	gotoxy(20, 11);
	cout << "STAY    s or S" << endl;
	gotoxy(12, 12);
	cout << "Press any key to return to menu" << endl;
	gotoxy(30, 25);
	if (_kbhit())
	{
		_getch();
		clear_screen();
		start();
	}
}

void ThePacmanGame::printScore() const
{
	setTextColor(Color::WHITE);
	gotoxy(Board::info.getX(), Board::info.getY());
	cout << "Score: " << ThePacmanGame::score;
}

void ThePacmanGame::printLives() const
{
	setTextColor(Color::WHITE);
	gotoxy(Board::info.getX() +9, Board::info.getY());
	cout << " | Lives: " << ThePacmanGame::lives;
}

void ThePacmanGame::printPause() const
{
	setTextColor(WHITE);
	if (Board::info.getY() > 15)
	{
		gotoxy(Board::info.getX() +25, Board::maxY);
		cout << "Game paused,";
		gotoxy(Board::info.getX() + 25, Board::maxY + 1);
		cout << "press any key";
		gotoxy(Board::info.getX() + 25, Board::maxY + 2);
		cout << "to continue";
	}
	else
	{
		gotoxy(Board::info.getX(), Board::info.getY() + 1);
		cout << "Game paused,";
		gotoxy(Board::info.getX(), Board::info.getY() + 2);
		cout << "press any key";
		gotoxy(Board::info.getX(), Board::info.getY() + 3);
		cout << "to continue";
	}
}

void ThePacmanGame::printContinue() const
{
	if (Board::maxX > 70)
	{
		gotoxy(10, Board::maxY + 1);
		cout << "             ";
		gotoxy(10, Board::maxY + 2);
		cout << "             ";
		gotoxy(10, Board::maxY + 3);
		cout << "             ";
	}
	else
	{
		gotoxy(Board::info.getX(), Board::info.getY() + 1);
		cout << "             ";
		gotoxy(Board::info.getX(), Board::info.getY() + 2);
		cout << "             ";
		gotoxy(Board::info.getX(), Board::info.getY() + 3);
		cout << "             ";
	}
}

void ThePacmanGame::printLevel(int i) const
{
	Sleep(200);
	clear_screen();
	hideCursor();
	if (Board::colored) { setTextColor(Color::WHITE); }
	gotoxy(20, 10);
	cout << " |LET's GO!|";
	if (Board::colored) { setTextColor(Color::LIGHTBLUE); }
	gotoxy(20, 11);
	cout << "|  Level " << i + 1 << "  |";
	Sleep(1300);
}

void ThePacmanGame::printGhostLevel()
{
	clear_screen();
	printFrame();
	gotoxy(19, 9);
	if (Board::colored) { setTextColor(Color::GREEN); }
	cout << "(1) ";
	if (Board::colored) { setTextColor(Color::WHITE); }
	cout << "NOVICE";
	gotoxy(19, 10);
	if (Board::colored) { setTextColor(Color::GREEN); }
	cout << "(2) ";
	if (Board::colored) { setTextColor(Color::WHITE); }
	cout << "GOOD";
	gotoxy(19, 11);
	if (Board::colored) { setTextColor(Color::GREEN); }
	cout << "(3) ";
	if (Board::colored) { setTextColor(Color::WHITE); }
	cout << "BEST";

	gotoxy(1, 24);
	setTextColor(WHITE);

	char choose;

	choose = _getch();
	switch (choose) {
	case '1': //
		ghostLevel = NOVICE;
		break;
	case '2': //
		ghostLevel = GOOD;
		break;
	case '3': //
		ghostLevel = BEST;
		break;
	}
}

void ThePacmanGame::printScreenChoice()
{
	clear_screen();
	printFrame();
	gotoxy(8, 9);
	if (Board::colored) { setTextColor(Color::GREEN); }
	cout << "(1) ";
	if (Board::colored) { setTextColor(Color::WHITE); }
	cout << "Run all screens available";
	gotoxy(8, 10);
	if (Board::colored) { setTextColor(Color::GREEN); }
	cout << "(2) ";
	if (Board::colored) { setTextColor(Color::WHITE); }
	cout << "Run a screen by name";

	gotoxy(1, 24);
	setTextColor(WHITE);

	char choose;

	choose = _getch();
	switch (choose) {
	case '1': //
		screens = MULTIPLE;
		break;
	case '2': //
		screens = SINGLE;
		break;
	}
}

void ThePacmanGame::checkChoice()
{
	char choose;
	do 
	{
		choose = _getch();
		switch (choose) {
		case START: // Start the game
			Board::colored = true;
			runByScreens();
			try { checkBoardExist(); }
			catch (NoBoardsException& n) {return;};
			break;
		case STARTWOC:
			Board::colored = false;
			runByScreens();
			try { checkBoardExist(); }
			catch (NoBoardsException& n) { return; };
			break;
		case INSTRUCTIONS: // Print instructions
			printInstructions();
			break;
		case EXIT:// EXIT
			printGoodBye();
			wannaPlay = false;
			break;
		default:
			choose = _getch();
			continue;
		}
	} while (wannaPlay);
}
 
void ThePacmanGame::runByScreens()
{
	printGhostLevel();
	printScreenChoice();
	init();
	try { checkBoardExist(); }
	catch (NoBoardsException& n) {
		clear_screen();
		cout << n.what() << endl;
		return;
	};
	if (screens == MULTIPLE)
	{
		Board::fileNamesList.front();
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
				gameOver();
			Board::pacmanCount = 0; Board::ghostCount = 0;
		}
	}
	else if (screens == SINGLE)
	{
		b.readScreens(Board::singleScreenName);
		if (!isBoardValid())
		{
			wannaPlay = false;
			return;
		}
		run(Board::singleScreenName);
		if (!lives)
			gameOver();
	}
	if (lives)
		win();
	return;
}

bool ThePacmanGame::isBoardValid()
{
	if (Board::pacmanCount != 1)
	{
		clear_screen();
		gotoxy(0, 0);
		setTextColor(WHITE);
		cout << "The file is not valid. No pacman or too many.\n\n";
		return false;
	}
	else if ((Board::ghostCount == 0) || (Board::ghostCount > 4))
	{
		clear_screen();
		gotoxy(0, 0);
		setTextColor(WHITE);
		cout << "The file is not valid. No ghosts or too many.\n\n";
		return false;
	}
	else return true;
}

void ThePacmanGame::win()
{
	Sleep(2000);
	clear_screen();
	Sleep(200);
	if (Board::colored) { setTextColor(Color::GREEN); }
	gotoxy(20, 11);
	cout << "YOU WON!" << endl;
	gotoxy(12, 12);
	setTextColor(Color::WHITE);
	cout << "press any key to continue" << endl;
	_getch();
	setTextColor(Color::WHITE);
	gotoxy(1, 24);
	clear_screen();

	printMenu();
	checkChoice();
}

void ThePacmanGame::gameOver()
{
	for (int i = 0; i < 4; i++)
	{
		if (Board::colored) { setTextColor(Color::RED); }
		gotoxy(20, 12);
		cout << "         ";
		Sleep(200);
		gotoxy(20, 12);
		cout << "GAME OVER" << endl;
		Sleep(200);
	}
	gotoxy(20, 12);
	cout << "GAME OVER" << endl;
	Sleep(2000);
	setTextColor(Color::WHITE);
	gotoxy(1, 24);
	clear_screen();
	
	printMenu();
	checkChoice();
}

void ThePacmanGame::setColors(Pacman& p, Ghost* g[], Fruit f)
{
	g[0]->setColor(LIGHTGREEN);
	g[1]->setColor(LIGHTMAGENTA);
	g[2]->setColor(LIGHTCYAN);
	g[3]->setColor(LIGHTRED);

	p.setColor(YELLOW);
	f.setColor(GREEN);
}

Point ThePacmanGame::nextPos(Point pos, int dir) const
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

bool ThePacmanGame::isBreadCrumb(Point pos)
{
	if (b.getPoint(pos) == '.')
		return true;
	else if ((b.getPoint(pos) == '%') || (b.getPoint(pos) == '$'))
		return false;
	else
		return false;
}

void ThePacmanGame::pacmanVsGhosts(Pacman& p, Ghost* g[],string name)
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

void ThePacmanGame::pacmanVsFruit(Pacman& p, Fruit& f)
{
	// Checking if pacman has the same location as the fruit
	if (p.getPos()==f.getPos())
	{
		score += f.getFigure()-'0';
		printMotivation();
		f.changeVisible();
	}
}

void ThePacmanGame::printMotivation()
{
	vector<string> motivation = { "YOU ROCK!", "LET'S GO!","YOU'RE SOMTHING ELSE!", "PAC-KING!", "BRING IT HOME!"};
	int i = rand() % motivation.size();
	Color color = Color(rand() % 16);
	gotoxy(Board::info.getX() + 2, Board::info.getY() + 1);
	setTextColor(color);
	cout << motivation[i];
	Sleep(700);
	gotoxy(Board::info.getX() + 2, Board::info.getY() + 1);
	cout << "                     ";
}

void ThePacmanGame::ghostsMove(bool& wait, bool& stop, bool& isCrumb, Ghost* g[], Pacman &p)
{
	Point next;
	if ((!wait) && (!stop))
	{
		for (int i = 0; i < Board::ghostCount; i++)
		{
			isCrumb = (isBreadCrumb(g[i]->getPos()));
			g[i]->move(isCrumb, p.getPos(), b);
			ghostsVsGhost(i, g);
		}

		wait = true;
	}
	else 
		wait = false;	
}

void ThePacmanGame::ghostsVsGhost(int i, Ghost* g[])
{
	for (int j = 0; j < 4; j++)
	{
		if (i != j)
			if (g[i]->getPos() == g[j]->getPos())
				g[i]->setDirection(rand()%4);
		return;
	}
}

void ThePacmanGame::fruitsMove(bool& wait, bool& stop, bool& isCrumb, Fruit& f, Pacman& p)
{
	Point next;
	if ((!wait) && (!stop))
	{
		isCrumb = (isBreadCrumb(f.getPos()));
		next = nextPos(f.getPos(), f.getDirection());
		while (b.getPoint(next) == '#')
		{
			f.setDirection(rand() % 4);
			next = nextPos(f.getPos(), f.getDirection());
		}

		f.move(isCrumb);
	}
}

void ThePacmanGame::printGoodBye()
{
	clear_screen();
	gotoxy(20, 12);
	cout << "GoodBye!" << endl;
	gotoxy(30, 25);
}

void ThePacmanGame::handlePacmanMove(Pacman& p, char& key, int& dir, Point& next)
{
	//Pacman move
	if (_kbhit())
	{
		key = _getch();
		if ((dir = p.changeDirection(key)) != ESC)
			p.setDirection(dir);
	}

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
}

void ThePacmanGame::handleFruitActivity(Fruit& f)
{
	//check if fruit is visible
	if (f.getVisible()) // fruit is visible
	{
		if ((rand() % 60) == 1)// rand to unactivate
		{
			f.changeVisible();
			f.erase(isBreadCrumb(f.getPos()));
		}
	}
	else //fruit is unvisible
	{
		if ((rand() % 25) == 1) // rand activate fruit
		{
			f.changeVisible();
			Point pos = f.randPosition();
			while (b.getPoint(pos) == '#' || b.getPoint(pos) == '%')
				pos = f.randPosition();
			f.randValue();
			f.setPosition(pos);
		}
	}
}

void ThePacmanGame::createNewfileNames(const string& name, string& stepsFileName, string& resultFileName)
{
	string delimiter = ".screen.txt";
	stepsFileName = name.substr(0, name.find(delimiter)) + ".steps.txt";
	resultFileName = name.substr(0, name.find(delimiter)) + ".result.txt";
}
