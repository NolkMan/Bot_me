#ifndef __BOTME_INC_CONFIG_READER_H
#define __BOTME_INC_CONFIG_READER_H

#include <string>

namespace config {
	struct Config {
		struct GeneralConf{
			int defaultGameID = 0;
		}general;

		struct WildWestConf{
			int cows = 20, milking = 20;
			int mapsize = 20;
			int dimension = 2;
		}wwconf;

	};

	Config readConfig(std::string);
}

#endif
