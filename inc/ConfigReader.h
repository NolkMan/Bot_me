#ifndef __BOTME_INC_CONFIG_READER_H
#define __BOTME_INC_CONFIG_READER_H

#include <string>

namespace config {
	struct Config {
		int mapSizeX, mapSizeY;
		Config ():mapSizeX(10),mapSizeY(10){}
	};

	Config readConfig(std::string);
}

#endif
