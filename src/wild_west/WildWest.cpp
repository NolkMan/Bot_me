#include "wild_west/WildWest.h"

#include <iostream>
#include <thread>
#include <chrono>

WildWest::WildWest(config::Config config, CommunicationManager *com):Game(config, com),
		gen(std::random_device()()){
	for (int i = 1 ; i < config.wwconf.cows+1 ; i++) {
		cow c;
		c.x = randomPosition();
		c.timeToMilk = config.wwconf.milking;
		c.id = i;
		cows[i] = c;
	}
	for (int i=0; i < config.wwconf.sellpoints; i++){
		points.push_back({randomPosition()});
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

bool WildWest::isSamePosition(const std::vector<int> &a,const std::vector<int> &b){
	for (int i=0 ; i < config.wwconf.dimension; i++)
		if (a[i] != b[i])
			return false;

	return true;
}

bool WildWest::isSellPointAt(const std::vector<int> &pos){
	for (const auto& sp : points)
		if (isSamePosition(pos, sp.x))
			return true;

	return false;
}

void WildWest::start(){
	std::cout << "WildWest started\n";
	commManager->gameStarted();

	for (;;){
		if (commManager->gameShouldClose()){
			break;
		}

		auto mess = commManager->getNextMessages();

		// Process messages
		for (const auto& mes : mess){
			unsigned int pid = mes.pid;
			auto com = mes.text;
			
			if ( players.count(pid) == 0 )
				players[pid] = newPlayer();

			if (com.size() >= 1){
				if (com[0] == 'm'){
					try{
						unsigned int id = std::stoul(com.substr(2));
						if (cows.count(id) == 1 && cows[id].timeToMilk == 0 &&
								isSamePosition(cows[id].x, players[pid].x)){
							cows[id].timeToMilk = config.wwconf.milking;
							players[pid].milked = true;
						}
					}catch(...){}
				}
				if (com[0] == 't'){
					try{
						unsigned int id = std::stoul(com.substr(2));
						if (cows.count(id) == 1 && isSamePosition(cows[id].x , players[pid].x)){
							players[pid].holding = true;
							players[pid].cow = id;
						}
					}catch(...){}
				}
				if (com[0] == 'd'){
					players[pid].holding = false;
				}
			}
			if (com.size() >= 2){
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

				if (players[pid].holding){
					cows[players[pid].cow].x = players[pid].x;
				}
			}
		}

		// Regrow milk
		for (auto& [k, c] : cows){
			if (c.timeToMilk != 0){
				c.timeToMilk--;
			}
		}

		// Sell milk
		for (auto& [k, pd] : players)
			if (pd.milked && isSellPointAt(pd.x)){
				pd.score ++;
				pd.milked = false;
				break;
			}

		// Do logic of player to player iteractions
		// If two players meet and one has milk while other does not it is stolen
		for (auto it = players.begin(); it != players.end(); it ++){
			auto ot = it;
			for (ot++; ot != players.end(); ot++){
				auto &pd = it->second;
				auto &od = it->second;
				if (isSamePosition( pd.x, od.x)){
					if (pd.milked != od.milked){
						pd.milked = !pd.milked;
						od.milked = !od.milked;
					}
				}
			}
		}

			
		// Crafting a response for all clients that sent a message
		for (const auto& m: mess){
			std::string res = "";
			unsigned int pid = m.pid;
			// Coords
			for (int i=0 ; i < config.wwconf.dimension ; i++){
				res += std::to_string(players[pid].x[i]);
				if (i < config.wwconf.dimension - 1){
					res += ',';
				}
			}
			res += ':';
			// Player has milk
			if (players[pid].milked) res += '1';
			else res += '0';
			res += ':';
			//Player is holding a cow
			// If no cow empty
			if (players[pid].holding) res += std::to_string(players[pid].cow);
			res += ':';
			// sell point here
			if (isSellPointAt(players[pid].x)) res += '1';
			else res += '0';
			res += ':';
			// cows
			for (const auto& [k, c] : cows){
				if (isSamePosition(players[pid].x, c.x)){
					res += std::to_string(c.id);
					res += ",";
				}
			}
			if (res[res.size()-1] == ','){
				res.pop_back();
			}
			res += ':';
			// Other players at the same square
			for (const auto& [k, pd] : players){
				if (isSamePosition(players[pid].x, pd.x)){
					res += std::to_string(k);
					res += ',';
				}
			}
			if (res[res.size()-1] == ','){
				res.pop_back();
			}

			commManager->addResponse(pid, res);
		}
		std::this_thread::sleep_for( std::chrono::milliseconds(30));
	}

	commManager->gameClosed();
	std::cout << "WildWest ended\n";
}
