#include "config_reader.h"
#include <fstream>
#include <iostream>

namespace config {
	namespace {
		void writeSetting( std::string setting, std::string value , Config &conf){
			if (setting == "MAP_SIZE_X")
				conf.mapSizeX = std::stoi(value);
			else if (setting == "MAP_SIZE_Y")
				conf.mapSizeY = std::stoi(value);
		}
	}

	Config readConfig (std::string fileloc){
		auto file = std::ifstream(fileloc);
		Config conf;
		std::string line;
		while (std::getline(file, line)){
			int col = line.find_first_of(":");
			auto setting = line.substr(0, col);
			auto value  = line.substr(col+1);
			writeSetting( setting, value, conf);
		}

		return conf;
	}
}

