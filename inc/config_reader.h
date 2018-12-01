#include <string>

namespace config {
	struct Config {
		int mapSizeX, mapSizeY;
		Config ():mapSizeX(10),mapSizeY(10){}
	};

	Config readConfig(std::string);
}


