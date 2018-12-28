#ifndef __BOTME_INC_WILDWEST_WILDWEST_H
#define __BOTME_INC_WILDWEST_WILDWEST_H

#include "Game.h"

#include <map>
#include <vector>

#include <random>

class WildWest : public Game {
	struct playerData{
		std::vector<int> x;
		bool holding;
		unsigned int cow;
		bool milked;
		unsigned int score;
	};
	struct cow{
		std::vector<int> x;
		int timeToMilk;
		unsigned int id;
	};
	struct sellpoint{
		std::vector<int> x;
	};

	std::map<unsigned int, playerData> players;
	std::map<unsigned int, cow> cows;
	std::vector<sellpoint> points;

	std::mt19937 gen;

	std::vector<int> randomPosition();
	playerData newPlayer();

	bool isSamePosition(const std::vector<int>&, const std::vector<int>&);
	bool isSellPointAt(const std::vector<int>&);

public:
	WildWest(config::Config, CommunicationManager*);

	void start();
};

#endif
