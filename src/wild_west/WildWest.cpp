#include "wild_west/WildWest.h"

#include <iostream>

WildWest::WildWest(config::Config config):Game(config),
		gen(std::random_device()()){
	for (int i = 0 ; i < config.wwconf.cows ; i++) {
		cow c;
		c.x = randomPosition();
		c.timeToMilk = config.wwconf.milking;
		c.id = i;
		cows.push_back(c);
	}
}

std::vector<int> WildWest::randomPosition(){
	std::vector<int> res;
	for (int i=0 ; i < config.wwconf.dimension; i++){
		unsigned int num = gen();
		res.push_back(num % config.wwconf.mapsize);
	}
	return res;
}

WildWest::playerData WildWest::newPlayer(){
	playerData pd;
	pd.x = randomPosition();
	pd.holding = 0;
	pd.milked = 0;
	pd.score = 0;
	return pd;
}

bool WildWest::isSamePosition(playerData pd, cow c){
	for (int i=0 ; i < config.wwconf.dimension; i++)
		if (c.x[i] != pd.x[i])
			return false;

	return true;
}

void WildWest::start(){
	std::cout << "WildWest started\n";
	commManager->gameStarted();

	for (;;){
		if (commManager->gameShouldClose()){
			break;
		}

		auto mess = commManager->getNextMessages();
		for (const auto& mes : mess){
			unsigned int pid = mes.pid;
			auto com = mes.text;
			
			if ( players.count(pid) == 0 )
				players[pid] = newPlayer();

			int dim = com[0] - '0';
			int dist = 0;
			if (com[1] == '+') dist = 1;
			if (com[1] == '-') dist = -1;
			if (!(0 <= dim && dim < config.wwconf.dimension)){
				dim = 0;
				dist= 0;
			}
			players[pid].x[dim] += dist;

			for (auto& x : players[pid].x){
				if (x < 0 ) x = 0;
				if (x > config.wwconf.mapsize) 
					x = config.wwconf.mapsize;
			}

			std::string res = "";
			for (int i=0 ; i < config.wwconf.dimension ; i++){
				res += std::to_string(players[pid].x[i]);
				if (i < config.wwconf.dimension - 1){
					res += ',';
				}
			}
			res += ':';
			for (const auto& c : cows){
				if (isSamePosition(players[pid], c)){
					res += std::to_string(c.id);
					res += ",";
				}
			}

			if (res[res.size()-1] == ','){
				res.pop_back();
			}

			commManager->addResponse(pid, res);
		}
	}

	commManager->gameClosed();
	std::cout << "WildWest ended\n";
}
