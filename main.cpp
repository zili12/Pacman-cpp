#include <windows.h>
#include <iostream>
using namespace std;

#include "ThePacmanGame.h"
#include "ThePacmanGameSave.h"
#include "ThePacmanGameLoad.h"
#include "ThePacmanGameSilent.h"
#include "InputParser.h"
#include "InvalidGameModeException.h"


void main(int argc, char** argv) 
{
	srand(time(NULL));
	ThePacmanGame* game;
	if (argc < 2) {
		ThePacmanGame simpleGame;
		game = &simpleGame;
		game->start();
	}
	else {
		
		InputParser input(argc, argv);
		
		try {input.checkMode();}
		catch (InvalidGameModeException& i)
		{
			cout << i.what() << endl;
			cout << "Usage: " << argv[0] << "[-save] [-load | -load -silent]" << endl;
			
		}
		if (input.mode == SAVE)
		{
			ThePacmanGameSave saveGame;
			game = &saveGame;
			game->start();
		}
		if (input.mode == LOAD)
		{
			ThePacmanGameLoad loadGame;
			game = &loadGame;
			game->start();
		}
		if (input.mode == SILENT)
		{
			ThePacmanGameSilent silentGame;
			game = &silentGame;
			game->start();
		}
	}
}
		


