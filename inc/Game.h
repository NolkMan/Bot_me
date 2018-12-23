#ifndef __BOTME_INC_GAME_H
#define __BOTME_INC_GAME_H

#include "ConfigReader.h"
#include "CommunicationManager.h"

class Game{
	config::Config config;
	CommunicationManager *commManager;
public:
	Game(config::Config config);
	virtual ~Game();

	void setCommunicationManager(CommunicationManager*);

	virtual int start() = 0;
private:
};

#endif
