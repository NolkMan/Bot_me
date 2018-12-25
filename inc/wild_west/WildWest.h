#ifndef __BOTME_INC_WILDWEST_WILDWEST_H
#define __BOTME_INC_WILDWEST_WILDWEST_H

#include "Game.h"

#include <map>
#include <vector>

#include <random>

class WildWest : public Game {
	struct playerData{
		std::vector<int> x;
		unsigned int holding;
		unsigned int milked;
		unsigned int score;
	};
	struct cow{
		std::vector<int> x;
		int timeToMilk;
		unsigned int id;
	};

	std::map<unsigned int, playerData> players;
	std::vector<cow> cows;

	std::mt19937 gen;

	std::vector<int> randomPosition();
	playerData newPlayer();

	bool isSamePosition(playerData, cow);

public:
	WildWest(config::Config);

	void start();
};

#endif
