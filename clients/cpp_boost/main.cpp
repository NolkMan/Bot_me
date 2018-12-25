#include "Client.cpp"

#include <thread>

#include <iostream>

int main(){
	Client cli = Client("0.0.0.0", 3200);

	std::thread(&Client::run, &cli).detach();

	while (!cli.isRunning());

	cli.addMessage("nolkman\n");
	cli.addMessage("nolkman\n");

	while (1){
		if (cli.isResponse()){
			auto str = cli.getResponse();
			std::cout << str << "\n";
			if (str == "Registered!"){ break; }
			cli.popResponse();
		}
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	cli.close();

	while (cli.isRunning());

	std::cout << "Nicely ended\n";

}

