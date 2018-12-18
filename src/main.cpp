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

	Game *game = new TestGame(config);
	auto comm = new CommunicationManager();

	game->setCommunicationManager(comm);

	try{
		auto server = Server(3200);

		server.setCommunicationManager(comm);

		std::thread(&Server::run, &server).detach();

		game->start();

	}catch( std::exception& e){
		std::cerr << e.what() << "\n";
	}

	std::cout << config.mapSizeX << " " << config.mapSizeY << "\n";

	delete game;

	return 0;
}
