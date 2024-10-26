#include "GitHubApiClient.h"
#include "GitHubUserEventsParser.h"
#include "GitHubUsernameValidator.h"


#include <iostream>
#include <string>


#pragma comment(lib, "wininet.lib")


int main(int argc, char* argv[]) {
	try {
		if (argc == 1) {
			throw std::runtime_error("Error:\tThe username is missing.\n");
		}

		std::string username{ argv[1] };
		if (GitHub::UsernameValidator::IsValidUsername(username)) {
			throw std::runtime_error("Error:\tThe username is invalide.\n");
		}

		std::string endpoint{ GitHub::ApiClient::GetUserEventsEndpoint(username) };

		std::cout << "\nSend a request to the GitHub server.\n";
		std::string json{ GitHub::ApiClient::SendGetRequest(endpoint) };
		std::cout << "\nReceive a response from the server.\n\n";

		auto events{ GitHub::UserEventsParser::Parse(json) };

		GitHub::UserEventsParser::Print(events);

	}
	catch (const std::runtime_error& exception) {
		std::cout << exception.what();
		return 1;
	}

	return 0;
}
