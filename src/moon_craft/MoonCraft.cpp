#include "moon_craft/MoonCraft.h"

#include <iostream>

MoonCraft::MoonCraft(config::Config config, CommunicationManager *com):Game(config, com){
}

void MoonCraft::start(){
	std::cout << "MoonCraft started!\n";

	for (;;){
		if (commManager->gameShouldClose()) break;
		std::this_thread::sleep_for(std::chrono::milliseconds( 30 ));
	}

	std::cout << "Game ended!\n";
}
