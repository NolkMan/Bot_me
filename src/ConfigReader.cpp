#include "ConfigReader.h"
#include <fstream>
#include <iostream>

namespace config {
	namespace {
		void writeWWSetting( std::string prefix, std::string value, Config &conf){
			if (prefix == "COWS"){
				conf.wwconf.cows = std::stoi(value);
			}
			if (prefix == "MILK"){
				conf.wwconf.milking = std::stoi(value);
			}
			if (prefix == "MAPS"){ 
				conf.wwconf.mapsize = std::stoi(value);
			}
			if (prefix == "DIM"){
				conf.wwconf.mapsize = std::stoi(value);
			}
		}

		void writeGenSetting(std::string prefix, std::string value, Config& conf){
			if (prefix == "DEFGAME"){
				conf.general.defaultGameID = std::stoi(value);
			}
		}

		void writeSetting( std::string setting, std::string rest , Config &conf){
			int col = rest.find_first_of(":");
			auto prefix = rest.substr(0,col);
			auto value = rest.substr(col+1);
			if (setting == "WW"){
				writeWWSetting(prefix, value, conf);
			}
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

