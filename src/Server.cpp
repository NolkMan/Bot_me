#include "Server.h"

#include <iostream>
#include <thread>
#include <chrono>

using boost::asio::ip::tcp;

Server::Server(int port):port(port),acceptor(io_service, tcp::endpoint(tcp::v4(), port)){
	acceptor.non_blocking(true);
}

void Server::startConnection(tcp::socket sock){
	int cid = commManager->createNewClient();
	try{
		//time out mechanism
		auto lastCall = std::chrono::steady_clock::now();
		auto now = lastCall;

		boost::asio::streambuf b;
		std::istream stream(&b);

		for (;;){
			boost::system::error_code error;

			// used to receive messages from the client
			if (sock.available()){
				boost::asio::read_until(sock, b, '\n', error);
				lastCall = std::chrono::steady_clock::now();

				if (error == boost::asio::error::eof){ break;
				}else if(error){ throw boost::system::system_error(error);
				}else{
					std::string message;
					while (std::getline(stream, message))
						commManager->addMessage(message, cid);
					stream.clear();
				}
			}

			now = std::chrono::steady_clock::now();
			if (std::chrono::duration_cast<std::chrono::seconds>(now - lastCall).count() > 5){
				std::cerr << "cid:" << cid << ":timeouted\n";
				std::string s = "You have been timed out\n";
				boost::asio::write(sock, boost::asio::buffer(s));
				break;
			}

			//used to send messages to the client
			while (commManager->isResponse(cid)){
				std::string resp = commManager->getResponse(cid);
				boost::asio::write(sock, boost::asio::buffer(resp));
				commManager->popResponse(cid);
			}

			if (commManager->shouldCloseClient(cid)){
				break;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(30));
		}

	}catch (std::exception& e){
		std::cerr << "[Server::startConnection] Exception while communicating with client: " << e.what() << "\n";
	}

	commManager->closedClient(cid);
	std::cout << "cid:" << cid << ":disconnected\n";
}

void Server::setCommunicationManager(CommunicationManager *cm){
	commManager = cm;
}

void Server::run(){
	commManager->startedServer();
	boost::system::error_code error;
	try{
		for(;;){
			tcp::socket sock(io_service);
			acceptor.accept(sock, error);
			if (!error)
				std::thread(&Server::startConnection, this, std::move(sock)).detach();
			else if (error != boost::asio::error::try_again)
				throw boost::system::system_error(error);

			if (commManager->shouldCloseServer()) break;

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}catch(std::exception &e){
		std::cerr << "[Server::run] Exception: " << e.what() << "\n";
	}
	commManager->closedServer();
}
