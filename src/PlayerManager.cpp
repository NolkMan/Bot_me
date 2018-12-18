#include "PlayerManager.h"

#include <fstream>
#include <iostream>

PlayerManager& PlayerManager::get(){
	static PlayerManager instance;
	return instance;
}

PlayerManager::PlayerManager(){
	readUsers();
}

void PlayerManager::addUser(std::string uname, std::string passwd){
	if (userHashes.count(uname) != 0 ){
		std::cerr << "User with that name already exists\n";
		return;
	}
	userHashes[uname] = passwd;
	writeUsers();
}

int PlayerManager::tryLogin(std::string uname, std::string passwd){
	if (userHashes.count(uname) == 0){
		std::cerr << "User tried to login with name that does not exist: " << uname << "\n";
		return 0;
	}
	if (userHashes[uname] == passwd){
		std::cout << "User with login: " << uname << " just logged in\n";
		return 1;
	}

	std::cout << "User with login: " << uname << " failed to log in\n";
	return 0;
}

void PlayerManager::readUsers(){
	std::ifstream file("users");
	std::string line, uname, passwd;

	userHashes.clear();

	while (std::getline(file,line)){
		int colon = line.find_first_of(":");
		if (colon == std::string::npos){
			std::cerr << "!!!    Users file corrupted    !!!\n";
			continue;
		}
		uname = line.substr(0,colon);
		passwd = line.substr(colon+1);
		userHashes[uname] = passwd; 
	}
}

void PlayerManager::writeUsers(){
	std::ofstream file("users");
	for(auto const& [uname, passwd] : userHashes){
		file << uname << ":" << passwd << "\n";
	}
}
