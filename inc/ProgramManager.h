#ifndef __BOTME_INC_PROGRAMMANAGER_H
#define __BOTME_INC_PROGRAMMANAGER_H

#include <map>

#include "CommunicationManager.h"
#include "ConfigReader.h"

#include "Game.h"
#include "Server.h"

/**
 * Class used to keep data about what threads are currently running
 */

enum class GameName{
	wild_west,
	moon_craft
};

class ProgramManager {
public:
	struct gameData{
		int gid;
		unsigned int port;
		GameName gameName;
		CommunicationManager *comm;
		Game *game;
		Server *server;
		const std::string getGameString() const{
			if (gameName == GameName::wild_west) return "Wild West";
			if (gameName == GameName::moon_craft) return "Moon craft";
			return "Invalid";
		}
	};
private:
	std::map<int, gameData> games;
	config::Config defaultConfig;

	int currentGid = 0;

public:
	ProgramManager(std::string confFile = "default_config.conf");
	
	/** Will create new game on new threads on specified port
	 * @param game is as game to start from enum
	 * @param port if -1 will try to start game on new free port
	 */
	void createNewGame(GameName, int port = -1);
	void createNewGame(GameName, int port, config::Config config);
	std::map<int, gameData>	getRunningGames();

	std::map<int, client> getClientsInGame(int gid);
	void disconnectClient(int gid, int cid);

	//* will wait untill server is closed
	void closeGame(int gid);

	struct InvalidGidException : std::exception{
		const char* what() const noexcept { return "Invalid gid given to ProgramManager"; }
	};
};

#endif
