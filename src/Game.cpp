#include "Game.h"

Game::Game(config::Config config){
	config = config;
}

Game::~Game(){}

void Game::setCommunicationManager(CommunicationManager *com){
	commManager = com;
}


