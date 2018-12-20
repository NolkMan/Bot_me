#include "PlayerManager.h"

#include <fstream>
#include <iostream>

PlayerManager& PlayerManager::get(){
	static PlayerManager instance;
	return instance;
}

PlayerManager::PlayerManager(){
	rng.seed(std::random_device()());
	readUsers();
}

void PlayerManager::addUser(std::string uname, std::string passwd){
	if (userHashes.count(uname) != 0 ){
		std::cerr << "User with that name already exists\n";
		return;
	}
	unsigned int pid;
	bool isIn = true;
	while (isIn) { 
		isIn = false; 
		pid = rng();
		for( const auto& [k , pd] : userHashes)
			if (pd.pid == pid) isIn = true;
	}

	userHashes[uname] = PlayerData(uname, passwd, pid);
	writeUsers();
}

PlayerManager::PlayerData PlayerManager::tryLogin(std::string uname, std::string passwd){
	if (userHashes.count(uname) == 0){
		std::cerr << "User tried to login with name that does not exist: " << uname << "\n";
		throw InvalidUserOrPassword();
	}
	if (userHashes[uname].passwd == passwd){
		return userHashes[uname];
	}

	std::cerr << "User with login: " << uname << " failed to log in\n";
	throw InvalidUserOrPassword();
}

void PlayerManager::readUsers(){
	std::ifstream file("users");
	std::string line, uname, passwd;
	int pid;

	userHashes.clear();

	while (std::getline(file,line)){
		int colon = line.find_first_of(":");
		int colon2 = line.find_first_of(":", colon+1);
		if (colon == std::string::npos || colon2 == std::string::npos){
			std::cerr << "!!!    Users file corrupted    !!!\n";
			continue;
		}
		uname = line.substr(0,colon);
		passwd = line.substr(colon+1, colon2 - colon - 1);
		pid = std::stoi(line.substr(colon2+1));

		userHashes[uname] = PlayerData(uname, passwd, pid); 
	}
}

void PlayerManager::writeUsers(){
	std::ofstream file("users");
	for(auto const& [uname, pd] : userHashes){
		file << pd.uname << ":" << pd.passwd << ":" << pd.pid << "\n";
	}
}
