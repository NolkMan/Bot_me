#ifndef __BOTME_INC_CONSOLEREADER_H
#define __BOTME_INC_CONSOLEREADER_H

#include "ProgramManager.h"

/**
 * Class that is responsible for managing cin and reading the console
 */
class ConsoleReader {
	ProgramManager *progManager;

	enum class Command { addUser, quit, showGames, showClients,
						 setGame, dropClient};

	std::map<std::string, Command> commands = { 
			{"adduser", Command::addUser}, // adduser <uname> <passwd>
			{"quit", Command::quit}, //quit
			{"showgames", Command::showGames}, //showgames
			{"showclients", Command::showClients}, //showclients
			{"setgame", Command::setGame}, //setgame <int>
			{"dropclient", Command::dropClient}, //dropclient int
		};
	
	int currentGid = 0;
public:
	ConsoleReader(ProgramManager *);

	void run();
};

#endif
