#include "ConsoleReader.h"

#include <iostream>
#include <vector>

#include "PlayerManager.h"

ConsoleReader::ConsoleReader(){
	comm = nullptr;
}

void ConsoleReader::setCommunicationManager(CommunicationManager *manager){
	comm = manager;
}

void ConsoleReader::run(){
	std::string message;
	while (std::getline(std::cin, message)){
		std::vector<std::string> args;
		int pos = 0, nextpos = 0;
		while (nextpos != std::string::npos){
			nextpos = message.find_first_of(" ", pos);
			args.push_back(message.substr(pos, nextpos-pos));
			pos = nextpos + 1;
		}

		if (commands.count(args[0]) == 0){
			std::cerr << "No such command as " << args[0] << "\n";
			continue;
		}

		Command command = commands[args[0]];

		if (command == Command::addUser){
			if (args.size() != 3){
				std::cerr << "To create a user username and password are needed.\n";
				continue;
			}

			if (args[1] == "" || args[2] == ""
			 || args[1].find(":") != std::string::npos
			 || args[2].find(":") != std::string::npos){
				std::cerr << "Invalid username or password\n"
						  << "Users can not contain ':' or be empty\n";
				continue;
			}

			PlayerManager::get().addUser(args[1], args[2]);
		}

	}
}



