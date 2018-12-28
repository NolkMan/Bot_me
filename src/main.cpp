#include <iostream>
#include <thread>

#include "Server.h"
#include "ConfigReader.h"
#include "ConsoleReader.h"
#include "PlayerManager.h"
#include "ProgramManager.h"

int main(int args, char ** argv){
	PlayerManager::get();

	ProgramManager *pm = new ProgramManager();

	auto consoleReader = ConsoleReader(pm);

	pm->createNewGame(GameName::wild_west, 3200);

	consoleReader.run();

	delete pm;

	return 0;
}
