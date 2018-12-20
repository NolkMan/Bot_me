#include <iostream>
#include <thread>

#include "server.h"
#include "config_reader.h"

#include "Game.h"
#include "TestGame.h"

int main(int args, char ** argv){
	std::string configFile;
	if (args == 1){
		configFile = "default_config.conf";
	}else{
		configFile = argv[1];
	}

	auto config = config::readConfig ( configFile );

	auto *comm = new CommunicationManager();

	Game *game = new TestGame(config);
	game->setCommunicationManager(comm);

	auto server = Server(3200);
	server.setCommunicationManager(comm);

	std::thread(&Server::run, &server).detach();
		
	game->start();
	

	delete game;
	delete comm;

	return 0;
}
