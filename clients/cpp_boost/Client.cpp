#include <boost/asio.hpp>

#include <iostream>

#include <queue>
#include <string>

#include <thread>
#include <mutex>

class Client{
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::endpoint endpoint;
	boost::asio::ip::tcp::socket socket;

	std::mutex mutex;

	std::queue<std::string> messages;
	std::queue<std::string> responses;

	bool serverRunning = false;
	bool shouldClose = false;

public:
	Client(std::string ip, unsigned short port):socket(io_service), 
			endpoint(boost::asio::ip::address::from_string(ip) , port)
	{
	}

	void addMessage(std::string message){
		std::lock_guard<std::mutex> lock(mutex);
		messages.push(message);
	}

	bool isResponse(){
		std::lock_guard<std::mutex> lock(mutex);
		return !responses.empty();
	}

	std::string getResponse(){
		std::lock_guard<std::mutex> lock(mutex);
		return responses.front();
	}

	void popResponse(){
		std::lock_guard<std::mutex> lock(mutex);
		responses.pop();
	}

	void close(){
		std::lock_guard<std::mutex> lock(mutex);
		shouldClose = true;
	}

	bool isRunning(){ 
		return serverRunning; 
	}

	void run(){
		{ std::lock_guard<std::mutex> lock(mutex); serverRunning = true; }

		socket.connect(endpoint);

		boost::asio::streambuf b;
		std::istream stream(&b);

		boost::system::error_code error;

		for (;;){
			// receiving
			if (socket.available()){
				boost::asio::read_until(socket, b, '\n', error);
				if (error == boost::asio::error::eof) { break; }
				else if (error) { break; }
				else {
					std::string message;
					while (std::getline( stream, message )){
						std::lock_guard<std::mutex> lock(mutex);
						responses.push( message );
					}
					stream.clear();
				}
			}

			// sending
			{
				std::lock_guard<std::mutex> lock(mutex);
				while (messages.size() > 0 ){
					std::string res = messages.front();
					boost::asio::write(socket, boost::asio::buffer(res), error);
					
					if (error){ break; }
					else { messages.pop(); }
				}
			}

			// closing
			{
				std::lock_guard<std::mutex> lock(mutex);
				if ( shouldClose ) break;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(30));
		}

		{ std::lock_guard<std::mutex> lock(mutex); serverRunning = false; }

	}

};
