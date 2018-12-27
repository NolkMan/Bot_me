#include "ProgramManager.h"

#include "TestGame.h"

ProgramManager::ProgramManager(std::string confFile):
		defaultConfig(config::readConfig(confFile))
{
}

void ProgramManager::createNewGame(GameName gn, int port){
	createNewGame(gn, port, defaultConfig);
}

void ProgramManager::createNewGame(GameName gameName, int port, config::Config conf){
	auto *comm = new CommunicationManager();

	int gid = currentGid; currentGid ++;

	
	Game *game = new TestGame(conf);
	game->setCommunicationManager(comm);
	
	auto *server = new Server(port);
	server->setCommunicationManager(comm);

	gameData gd = { gid,
			static_cast<unsigned int>(port),
			false,
			false,
			comm,
			game,
			server};

	games[gid] = gd;

	std::thread(&Server::run, server).detach();
	std::thread(&Game::start, game).detach();
}

std::map<int, ProgramManager::gameData> ProgramManager::getRunningGames(){
	return games;
}

std::map<int, client> ProgramManager::getClientsInGame(int gid){
	if (games.count(gid) == 0) throw InvalidGidException();
	
	return games[gid].comm->getCurrentClients();
}

void ProgramManager::disconnectClient(int gid, int cid){
	if (games.count(gid) == 0) throw InvalidGidException();
	games[gid].comm->closeClient(cid);
}

void ProgramManager::closeGame(int gid){
	if (games.count(gid) == 0) throw InvalidGidException();
	games[gid].comm->shutdown();
}

