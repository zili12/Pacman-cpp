#ifndef _THEPACMANGAMESILENT_H_
#define _THEPACMANGAMESILENT_H_

#include "ThePacmanGameLoad.h"

//ThePacmanGameLoad
class ThePacmanGameSilent : public ThePacmanGameLoad {
private:
	bool finalTest = true;
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
	void pacmanVsFruit(Pacman& p, Fruit& f) override;
	void ghostsMove(bool& wait, bool& stop, bool& isCrumb, Ghost* g[], Pacman& p) override;
	void fruitsMove(bool& wait, bool& stop, bool& isCrumb, Fruit& f, Pacman& p) override;
	void handlePacmanMove(Pacman& p, char& key, int& dir, Point& next) override;
};

#endif