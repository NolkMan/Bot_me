#ifndef __BOTME_INC_MOONCRAFT_MOONCRAFT_H
#define __BOTME_INC_MOONCRAFT_MOONCRAFT_H

#include "Game.h"

class MoonCraft : public Game {
public:
	MoonCraft(config::Config config);

	int start();
};

#endif
