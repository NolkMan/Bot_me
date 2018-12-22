#ifndef __BOTME_INC_COMM_MANAGER_H
#define __BOTME_INC_COMM_MANAGER_H

#include <string>
#include <queue>
#include <map>
#include <vector>
#include <thread>
#include <mutex>

struct message{
	std::string text;
	unsigned int pid;
};

struct client{
	unsigned int pid;
	std::string uname;
	bool registered;
	bool playing;
	int cid;
	std::queue<std::string> messages;
	std::queue<std::string> responses;
};

/**
 * Class used to communicate between threads of game, server and console reader
 * This class is fully thread-safe and threads should listen to it to check for new messages
 */
class CommunicationManager{
	int cpid = 0;
	int currentCid = 1;

	std::mutex maplock;
	std::map<int, client> clients;
public:
	/**
	 * Returns a single message from every connected user
	 */
	std::vector<message> getNextMessages();

	/**
	 * Methods used for server communication
	 */

	int createNewClient();
	void addMessage(std::string text, int cid);

	bool isResponse(int cid);
	std::string getResponse(int cid);
	void popResponse(int cid);
};

#endif
