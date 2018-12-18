#include "CommunicationManager.h"

#include <iostream>

#include "PlayerManager.h"

int CommunicationManager::createNewClient(){
	client c;
	c.registered = false;
	c.playing = false;
	c.pid = -1;
	c.cid = currentCid; currentCid ++;
	c.uname = "";

	c.responses.push("Enter username:\n");

	std::lock_guard<std::mutex> lock(maplock);
	clients[c.cid] = c;

	return c.cid;
}

void CommunicationManager::addMessage(std::string text, int cid){
	std::lock_guard<std::mutex> lock(maplock);

	client &c = clients[cid];

	if (!c.registered){
		if (c.uname == ""){
			c.uname = text;
			c.responses.push("Enter password:\n");
		}else{
			if (PlayerManager::get().tryLogin(c.uname , text)){
				c.pid = 1;
				c.registered = true;
				c.responses.push("Registered!\n");
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

