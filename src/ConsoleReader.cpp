#include "ConsoleReader.h"

#include <iostream>
#include <vector>

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

		if (command == Command::addPlayer){
			if (args.size() != 3){
				std::cerr << "To create a user username and password are needed.\n";
				continue;
			}

			// Create user here
		}

	}
}



