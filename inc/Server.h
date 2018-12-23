#ifndef __BOTME_INC_SERVER_H
#define __BOTME_INC_SERVER_H

#include "boost/asio.hpp"
#include "boost/bind.hpp"

#include "CommunicationManager.h"

/**
 * Server class 
 * Creates and manages the server
 */
class Server{
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::tcp::acceptor acceptor;
	
	static const int max_length = 1024;

	unsigned short port;

	CommunicationManager *commManager;

	/**
	 * Used to manage connection with a single user
	 */
	void startConnection(boost::asio::ip::tcp::tcp::socket);

public:
	/**
	 * Initializes server for running
	 * still needs setCommandManager function
	 */
	Server(int port);

	/**
	 * Function that actually binds and runs the server
	 * setCommandManager function must be called before this one
	 */
	void run();

	/**
	 * CommunicationManager is needed for server-game communication
	 */
	void setCommunicationManager(CommunicationManager*);
};

#endif

