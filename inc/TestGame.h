#ifndef __BOTME_INC_TESTGAME_H
#define __BOTME_INC_TESTGAME_H

#include "Game.h"

class TestGame : public Game {
public:
	TestGame(config::Config config);

	int start();
	int end();

};

#endif
