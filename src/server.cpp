#include "server.h"

#include <iostream>

using boost::asio::ip::udp;

Server::Server(int port):port(port),socket(io_service, udp::endpoint(udp::v4(), port)){
	socket.async_receive_from(
			boost::asio::buffer(data_, max_length), sender_endpoint_,
		   	boost::bind(&Server::handle_receive_from, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
}

void Server::run(){
	io_service.run();
}

void Server::handle_receive_from(
		const boost::system::error_code &error, 
		size_t bytes_recvd){
	if (!error && bytes_recvd > 0)
    {
      socket.async_send_to(
          boost::asio::buffer(data_, bytes_recvd), sender_endpoint_,
          boost::bind(&Server::handle_send_to, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      socket.async_receive_from(
          boost::asio::buffer(data_, max_length), sender_endpoint_,
          boost::bind(&Server::handle_receive_from, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
  }


void Server::handle_send_to(const boost::system::error_code& /*error*/,
      size_t /*bytes_sent*/){
	socket.async_receive_from(
		boost::asio::buffer(data_, max_length), sender_endpoint_,
		boost::bind(&Server::handle_receive_from, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

