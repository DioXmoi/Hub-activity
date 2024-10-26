#include "GitHubApiClient.h"
#include "GitHubUserEventsParser.h"
#include "UsernameValidator.h"


#include <iostream>
#include <string>



#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "wininet.lib")


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
	catch (const std::runtime_error& exception) {
		std::cout << exception.what();
		return 1;
	}

	return 0;
}
