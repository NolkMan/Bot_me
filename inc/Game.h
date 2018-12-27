#ifndef __BOTME_INC_GAME_H
#define __BOTME_INC_GAME_H

#include "ConfigReader.h"
#include "CommunicationManager.h"

class Game{
protected:
	config::Config config;
	CommunicationManager *commManager;
public:
	Game(config::Config config, CommunicationManager *);
	virtual ~Game();

	virtual void start() = 0;
private:
};

#endif
