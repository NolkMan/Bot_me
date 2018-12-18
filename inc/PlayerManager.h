#ifndef __BOTME_INC_PLAYERMANAGER_H
#define __BOTME_INC_PLAYERMANAGER_H

#include <string>
#include <map>

/* Singleton class used to manage what users are able to connect and their credentials
 */
class PlayerManager{
public:
	static PlayerManager& get();

	void addUser(std::string uname, std::string passwd);
	
	// returns pid or -1 when such user does not exist
	int tryLogin(std::string name, std::string passwd);

private:
	PlayerManager();
	
	// stores a hash belonging to a specific user
	std::map<std::string, std::string> userHashes;

	void readUsers();
	void writeUsers();

public:
	PlayerManager(PlayerManager const&) = delete;
	void operator=(PlayerManager const&) = delete;
};

#endif
