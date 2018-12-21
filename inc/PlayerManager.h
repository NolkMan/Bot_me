#ifndef __BOTME_INC_PLAYERMANAGER_H
#define __BOTME_INC_PLAYERMANAGER_H

#include <string>
#include <map>
#include <random>
#include <exception>
#include <thread>
#include <mutex>

/**
 * Singleton class used to manage what users 
 * Who is able to connect and credentials
 *
 * All of public methods of this class are thread safe
 */
class PlayerManager{
public:
	struct PlayerData{
		std::string uname;
		std::string passwd;
		unsigned int pid;
		PlayerData(std::string un="", std::string ps="", int p=-1):uname(un),passwd(ps),pid(p){}
	};

	struct InvalidUserOrPassword : std::exception {
		const char* what() const noexcept { return "Bad user or login during login\n"; }
	};

	/**
	 * returns the singleton of this class
	 */
	static PlayerManager& get();

	/**
	 * Adds an user to the database
	 */
	void addUser(std::string uname, std::string passwd);
	
	/**
	 * Checks the creadentials of the user
	 * Throws an exception when fails
	 */
	PlayerData tryLogin(std::string name, std::string passwd);

private:
	PlayerManager();
	
	// stores a hash belonging to a specific user
	std::map<std::string, PlayerData> userHashes;
	std::mutex databaseMutex;

	std::mt19937 rng;

	void readUsers();
	void writeUsers();

public:
	PlayerManager(PlayerManager const&) = delete;
	void operator=(PlayerManager const&) = delete;
};

#endif
