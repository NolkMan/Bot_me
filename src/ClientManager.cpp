#include "ClientManager.h"

#include <thread>

ClientManager::ClientManager(){
}

void ClientManager::addCommand(std::string command){
	std::lock_guard<std::mutex> lock(mutex);
	commands.push(command);
}

std::string ClientManager::getCommand(){
	std::lock_guard<std::mutex> lock(mutex);
	std::string	command = commands.front();
	commands.pop();
	return command;
}
