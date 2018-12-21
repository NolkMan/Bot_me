#ifndef __BOTME_INC_CONSOLEREADER_H
#define __BOTME_INC_CONSOLEREADER_H

#include "CommunicationManager.h"

/**
 * Class that is responsible for managing cin and reading the console
 */
class ConsoleReader {
	CommunicationManager *comm;

	enum class Command { addUser };

	std::map<std::string, Command> commands = { 
			{"adduser", Command::addUser} 
		};
public:
	ConsoleReader();
	
	void setCommunicationManager(CommunicationManager *);

	void run();
};

#endif
