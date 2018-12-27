#include "Game.h"

Game::Game(config::Config config,
		CommunicationManager *com){
	config = config;
	commManager = com;
}

Game::~Game(){}

