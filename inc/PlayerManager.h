#ifndef __BOTME_INC_PLAYERMANAGER_H
#define __BOTME_INC_PLAYERMANAGER_H

#include <string>
#include <map>
#include <random>
#include <exception>

/* Singleton class used to manage what users are able to connect and their credentials
 */
class PlayerManager{
public:
	struct PlayerData{
		std::string uname;
		std::string passwd;
		int pid;
		PlayerData(std::string un="", std::string ps="", int p=-1):uname(un),passwd(ps),pid(p){}
	};

	struct InvalidUserOrPassword : std::exception {
		const char* what() const noexcept { return "Bad user or login during login\n"; }
	};

	static PlayerManager& get();

	void addUser(std::string uname, std::string passwd);
	
	// returns pid or -1 when such user does not exist
	PlayerData tryLogin(std::string name, std::string passwd);

private:
	PlayerManager();
	
	// stores a hash belonging to a specific user
	std::map<std::string, PlayerData> userHashes;

	std::mt19937 rng;

	void readUsers();
	void writeUsers();

public:
	PlayerManager(PlayerManager const&) = delete;
	void operator=(PlayerManager const&) = delete;
};

#endif
