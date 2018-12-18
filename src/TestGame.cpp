#include "TestGame.h"

#include <iostream>

TestGame::TestGame(config::Config config):Game(config){
}

int TestGame::start(){
	std::cout << "Game started!\n";
	for (int i=0; i <= 100000000; i++){
	}
	while(true){}

	std::cout << "Game ended!\n";

	return 1;
}

int TestGame::end(){
	std::cout << "Game was tried to be ended!\nBut this game is shit\n";
	return 0;
}
