#ifndef __BOTME_SRC_SERVER_H
#define __BOTME_SRC_SERVER_H

#include "boost/asio.hpp"
#include "boost/bind.hpp"

class Server{
	boost::asio::io_service io_service;
	boost::asio::ip::udp::udp::socket socket;

	boost::asio::ip::udp::udp::endpoint sender_endpoint_;
	
	static const int max_length = 1024;
	char data_[max_length];

	int port;

public:
	Server(int port);

	void run();

	void handle_receive_from(const boost::system::error_code &error, 
		size_t bytes_recvd);
	void handle_send_to(const boost::system::error_code& , size_t );
};

#endif

