#ifndef _THEPACMANGAMESAVE_H_
#define _THEPACMANGAMESAVE_H_

#include "ThePacmanGame.h"

//ThePacmanGameSave
class ThePacmanGameSave : public ThePacmanGame {
private:
	// The game functions
	//void init();
	void run(string name) override;
	char DirectionToChar(const int direction);
	char yesOrNo(const bool argument);

public:
	//void start();
};

#endif