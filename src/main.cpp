#include <iostream>
#include <bits/stdc++.h>

#include "server.h"
#include "config_reader.h"

int main(int args, char ** argv){
	std::string configFile;
	if (args == 1){
		configFile = "default_config.conf";
	}else{
		configFile = argv[1];
	}

	auto config = config::readConfig ( configFile );

	try{
		auto server = Server(3200);

		server.run();
	}catch( std::exception& e){
		std::cerr << e.what() << "\n";
	}

	std::cout << config.mapSizeX << " " << config.mapSizeY << "\n";

	return 0;
}
