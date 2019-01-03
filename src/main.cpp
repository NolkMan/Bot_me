#include <iostream>
#include <thread>

#include "Server.h"
#include "ConfigReader.h"
#include "ConsoleReader.h"
#include "PlayerManager.h"
#include "ProgramManager.h"


#ifdef TESTING

#include "utests/SerializableTests.h"

int main(){
	for (int i=0 ; i < 4 ; i++){
		auto so = UnitTestSerialization(i).serialize();
		bool success;
		UnitTestSerialization(so, success);
		if (success){
			std::cout << "Unit test: " << i << " for SerializationObject passed\n";
		}else{
			std::cout << "Unit test: " << i << " for SerializationObject failed\n";
		}
	}

	return 0;
}
#else

int main(int args, char ** argv){
	PlayerManager::get();

	ProgramManager *pm = new ProgramManager();

	auto consoleReader = ConsoleReader(pm);

	pm->createNewGame(GameName::wild_west, 3200);

	consoleReader.run();

	delete pm;
	return 0;
}

#endif
