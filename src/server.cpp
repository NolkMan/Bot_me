#include "server.h"

#include <iostream>
#include <thread>
#include <chrono>

using boost::asio::ip::tcp;

Server::Server(int port):port(port),acceptor(io_service, tcp::endpoint(tcp::v4(), port)){
}

void Server::startConnection(tcp::socket sock){
	int cid = commManager->createNewClient();
	try{
		char data[max_length];
		boost::asio::streambuf b;
		std::istream stream(&b);

		for (;;){
			boost::system::error_code error;

			// used to receive messages from the client
			if (sock.available()){
				boost::asio::read_until(sock, b, '\n', error);

				if (error == boost::asio::error::eof){ // client disconnected
					break;
				}else if(error){ // other error
					throw boost::system::system_error(error);
				}else{
					std::string message;
					while(std::getline(stream, message))
						commManager->addMessage(message, cid);
				}
			}

			//used to send messages to the client
			while (commManager->isResponse(cid)){
				try{
					std::string resp = commManager->getResponse(cid);
					boost::asio::write(sock, boost::asio::buffer(resp));
					commManager->popResponse(cid);
				}catch(std::exception& e){
					std::cerr << "Error while sending a message: " << e.what() << "\n";
				}
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(30));
		}

	}catch (std::exception& e){
		std::cerr << "Exception while communicating with client " << e.what() << "\n";
	}

	std::cout << "Client disconnected\n";
}

void Server::setCommunicationManager(CommunicationManager *cm){
	commManager = cm;
}

void Server::run(){
	for(;;){
		tcp::socket sock(io_service);
		acceptor.accept(sock);
		std::thread(&Server::startConnection, this, std::move(sock)).detach();
	}
}
