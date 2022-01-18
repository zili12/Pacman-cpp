#ifndef _THEPACMANGAMELOAD_H_
#define _THEPACMANGAMELOAD_H_

#include "ThePacmanGame.h"

//ThePacmanGameLoad
class ThePacmanGameLoad : public ThePacmanGame {
private:
	// The game functions
	//void init();
	void run(string name) override;
//	void createNewfileNames(string name, string& stepsFileName, string& resultFileName);
	int charToDirection(const char& tmp);
	void directionToKey(char& key);

public:
	//void start();
	void start() override;
	void init() override;
	bool charToBool(const char& tmp);
	void runByScreens() override;
	void pacmanVsGhosts(Pacman& p, Ghost* g[], string name) override;
	void ghostsMove(bool& wait, bool& stop, bool& isCrumb, Ghost* g[], Pacman& p) override;
	void fruitsMove(bool& wait, bool& stop, bool& isCrumb, Fruit& f, Pacman& p) override;
	void handlePacmanMove(Pacman& p, char& key, int& dir, Point& next) override;
};

#endif