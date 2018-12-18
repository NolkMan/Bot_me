#ifndef __BOTME_INC_COMM_MANAGER_H
#define __BOTME_INC_COMM_MANAGER_H

#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <map>

struct message{
	std::string text;
	int pid;
};

struct client{
	bool registered;
	bool playing;
	int pid;
	int cid;
	std::string uname;
	std::queue<std::string> messages;
	std::queue<std::string> responses;
};

class CommunicationManager{
	int cpid = 0;
	int currentCid = 1;

	std::mutex maplock;
	std::map<int, client> clients;
public:
	message getNextMessage();

	int createNewClient();
	void addMessage(std::string text, int cid);

	bool isResponse(int cid);
	std::string getResponse(int cid);
	void popResponse(int cid);
};

#endif
