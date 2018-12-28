#include "ConsoleReader.h"

#include <iostream>
#include <vector>

#include "PlayerManager.h"

ConsoleReader::ConsoleReader(ProgramManager *pm):progManager(pm){
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
		if (command == Command::quit){
			auto data = progManager->getRunningGames();
			for (const auto& [key, gd] : data){
				progManager->closeGame(gd.gid);
			}

			break;
		}
		if (command == Command::showGames){
			auto data = progManager->getRunningGames();
			for( const auto& [key, gd] : data){
				std::cout << gd.getGameString() << ":" << gd.gid << ":" << gd.port <<"\n";
			}
		}
		if (command == Command::showClients){
			try{
				auto data = progManager->getClientsInGame( currentGid );
				for (const auto& [key, cd] : data){
					std::cout << cd.cid << ":" << cd.pid << ":" << cd.uname << ":" << cd.registered << "\n";
				}
			}catch(std::exception &e){
				std::cout << e.what() << "\n";
			}
		}
		if (command == Command::setGame){
			try{
				if (args.size() < 2){
					std::cout << "You need to specify what game you want to switch to\n";
					continue;
				}
				int newGid = std::stoi(args[1]);
				currentGid = newGid;
			}catch(std::exception &e){
				std::cout << e.what() << "\n";
			}
		}
		if (command == Command::dropClient){
			if (args.size() < 2){
				std::cout << "You need to specify client\n";
				continue;
			}
			try{
				int cid = std::stoi( args[1] );
				progManager->disconnectClient(currentGid, cid);
			}catch(std::exception &e){
				std::cout << e.what() << "\n";
			}
		}
	}
}

