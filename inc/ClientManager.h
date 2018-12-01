#ifndef __BOTME_INC_CLIENTMANAGER_H
#define __BOTME_INC_CLIENTMANAGER_H

#include <queue>
#include <mutex>

// UDP Server and Game Server are running on different threads, so this class is class managing communication between server and client
class ClientManager{
	std::mutex mutex;
	std::queue<std::string> commands;
	std::queue<std::string> responces;
public:
	ClientManager();	

	void addCommand(std::string);
	std::string getCommand();
	void addResponse(std::string);
	std::string getResponse();
};

#endif
