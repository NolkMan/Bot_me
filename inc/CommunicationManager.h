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
	bool close;

	bool registered;
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
	std::map<unsigned int, int> reverseMap;

	bool gameRunning = false;
	bool gameClosing = false;

	bool serverRunning = false;
	bool serverClosing = false;

public:

	// Data inspection
	// Note: it may change after returning
	
	bool isServerRunning();
	bool isGameRunning();

	std::map<int,client> getCurrentClients();

	// Blocks thread until all associeated threads are closed
	void shutdown();

	// Game
	
	/** Game control */
	void gameStarted();
	bool gameShouldClose();
	void gameClosed();

	/**
	 * Returns a single message from every connected user
	 */
	std::vector<message> getNextMessages();
	/**
	 * Will send a message to specific client
	 * \throw when pid does not map to any client
	 */
	void addResponse(unsigned int pid, std::string);

	/**
	 * Methods used for server communication
	 */

	// Server

	void startedServer();
	bool shouldCloseServer();
	void closedServer();

	// Client

	int createNewClient();
	void closedClient(int cid);
	
	void closeClient(int cid);
	bool shouldCloseClient(int cid);

	void addMessage(std::string text, int cid);

	bool isResponse(int cid);
	std::string getResponse(int cid);
	void popResponse(int cid);
public:
	struct InvalidPidException : std::exception {
		const char* what() const noexcept { return "Invalid pid give to CommunicationManager"; }
	};
};

#endif
