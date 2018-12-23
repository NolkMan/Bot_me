#include "moon_craft/MoonCraft.h"

#include <iostream>

MoonCraft::MoonCraft(config::Config config):Game(config){
}

int MoonCraft::start(){
	std::cout << "MoonCraft started!\n";


	for (;;){
	}

	std::cout << "Game ended!\n";
}
