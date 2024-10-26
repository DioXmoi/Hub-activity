#include "GitHubApiClient.h"
#include "GitHubUserEventsParser.h"
#include "UsernameValidator.h"

<<<<<<< HEAD
#include <array>
=======

>>>>>>> my-new-branch
#include <iostream>
#include <string>



#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "wininet.lib")


void print(std::array<Event, 17> events) {
	for (const auto& item : events) {
		std::cout << item.type << " " << item.count << '\n';
	}
}

int main(int argc, char* argv[]) {
	try {
		if (argc == 1) {
			throw std::runtime_error("Error:\tThe username is missing.\n");
		}

		std::string username{ argv[1] };
		if (UsernameValidator::IsValidUsername(username)) {
			throw std::runtime_error("Error:\tThe username is invalide.\n");
		}

		std::string endpoint{ GitHubApiClient::GetUserEventsEndpoint(username) };

		std::cout << "\nSend a request to the GitHub server.\n";
		std::string json{ GitHubApiClient::SendGetRequest(endpoint) };
		std::cout << "\nReceive a response from the server.\n\n";

		std::array events{ GitHubUserEventsParser::Parse(json) };

		GitHubUserEventsParser::Print(events);

	}
<<<<<<< HEAD

	std::string username{ argv[1] };
	if (!UsernameValidator::IsValidUsername(username)) {
		std::cout << "Error:\tThe username is invalide.\n";
		return 1;
	}

	std::string endpoint{ GetUserEventsEndpoint(username) };

	std::string json{ GitHubApiClient::SendGetRequest(endpoint) };

	auto events{ GitHubUserEventsParser::parse(json) };

	print(events);
=======
	catch (const std::runtime_error& exception) {
		std::cout << exception.what();
		return 1;
	}
>>>>>>> my-new-branch

	return 0;
}
