#ifndef __BOTME_INC_CONSOLEREADER_H
#define __BOTME_INC_CONSOLEREADER_H

#include "CommunicationManager.h"

class ConsoleReader {
	CommunicationManager *comm;

	enum class Command { addPlayer };

	std::map<std::string, Command> commands = { 
			{"addplayer", Command::addPlayer} 
		};
public:
	ConsoleReader();
	
	void setCommunicationManager(CommunicationManager *);

	void run();
};

#endif
