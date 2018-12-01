#include <iostream>
#include "config_reader.h"

int main(int args, char ** argv){
	if (args == 1){
		std::cout <<  "Please specify config file";
		return 0;
	}

	auto config = config::readConfig ( argv[1] );

	std::cout << config.mapSizeX << " " << config.mapSizeY << "\n";

	return 0;
}
