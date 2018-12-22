#include "CommunicationManager.h"

#include <iostream>

#include "PlayerManager.h"

// Data retrieval

bool CommunicationManager::isServerRunning(){
	return serverRunning;
}

// Game

std::vector<message> CommunicationManager::getNextMessages(){
	std::lock_guard<std::mutex> lock(maplock);
	std::vector<message> messages;
	for(auto& [cid, c] : clients){
		if (!c.messages.empty()){
			std::string message = c.messages.front();
			c.messages.pop();
			messages.push_back({message, c.pid});
		}
	}
	
	return messages;
}

void CommunicationManager::addResponse(unsigned int pid, std::string message){
	std::lock_guard<std::mutex> lock(maplock);
	if (reverseMap.count(pid) == 0){
		throw InvalidPidException();
		return;
	}

	unsigned int cid = reverseMap[pid];

	clients[pid].responses.push(message);
}

// Server

void CommunicationManager::startedServer(){
	std::lock_guard<std::mutex> lock(maplock);
	serverRunning = true;
}

void CommunicationManager::closedServer(){
	std::lock_guard<std::mutex> lock(maplock);
	serverRunning = false;
}

// Client

int CommunicationManager::createNewClient(){
	client c;
	c.registered = false;
	c.playing = false;
	c.pid = -1;
	c.close = false;
	c.cid = currentCid; currentCid ++;
	c.uname = "";

	c.responses.push("Enter username:\n");

	std::lock_guard<std::mutex> lock(maplock);
	clients[c.cid] = c;

	return c.cid;
}

void CommunicationManager::closedClient(int cid){
	std::lock_guard<std::mutex> lock(maplock);
	int pid = clients[cid].pid;
	if (reverseMap.count(pid) != 0){
		reverseMap.erase(pid);
	}
	clients.erase(cid);
}

bool CommunicationManager::shouldCloseClient(int cid){
	std::lock_guard<std::mutex> lock(maplock);
	return clients[cid].close;
}

void CommunicationManager::addMessage(std::string text, int cid){
	std::lock_guard<std::mutex> lock(maplock);

	client &c = clients[cid];

	if (!c.registered){
		if (c.uname == ""){
			c.uname = text;
			c.responses.push("Enter password:\n");
		}else{
			try{
				auto pd = PlayerManager::get().tryLogin(c.uname, text);
				if (reverseMap.count(pd.pid) != 0){
					c.close = true;
					c.responses.push("Another connection exists for that user\n");
				}else{
					reverseMap[pd.pid] = c.cid;
					c.pid = pd.pid;
					c.registered = true;
					c.responses.push("Registered!\n");
					std::cout << "cid:" << c.cid << ":registered as:" << c.uname << ":" << c.pid << "\n";
				}
			}catch(...){
				std::cerr << "[FAILED LOGIN] User: " << c.uname << "\n";
			}
		}
	}else{
		c.messages.push(text);
	}
}

bool CommunicationManager::isResponse(int cid){
	std::lock_guard<std::mutex> lock(maplock);
	return clients[cid].responses.size() > 0;
}

std::string CommunicationManager::getResponse(int cid){
	std::lock_guard<std::mutex> lock(maplock);
	return clients[cid].responses.front();
}

void CommunicationManager::popResponse(int cid){
	std::lock_guard<std::mutex> lock(maplock);
	clients[cid].responses.pop();
}

