#ifndef __BOTME_INC_SERVER_H
#define __BOTME_INC_SERVER_H

#include "boost/asio.hpp"
#include "boost/bind.hpp"

#include "CommunicationManager.h"

class Server{
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::tcp::acceptor acceptor;
	
	static const int max_length = 1024;

	unsigned short port;

	CommunicationManager *commManager;

	void startConnection(boost::asio::ip::tcp::tcp::socket);

public:
	Server(int port);

	void run();

	void setCommunicationManager(CommunicationManager*);

	void send( std::string, boost::asio::ip::tcp::tcp::endpoint);
};

#endif

