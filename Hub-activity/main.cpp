#include "GitHubApiClient.h"
#include "GitHubUserEventsParser.h"
#include "UsernameValidator.h"

#include <array>
#include <iostream>
#include <string>


#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "wininet.lib")

std::string GetUserEventsEndpoint(const std::string& username) {
	return "/users/" + username + "/events";
}

void print(std::array<Event, 17> events) {
	for (const auto& item : events) {
		std::cout << item.type << " " << item.count << '\n';
	}
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		std::cout << "Error:\tThe username is missing.\n";
		return 1;
	}

	std::string username{ argv[1] };
	if (!UsernameValidator::IsValidUsername(username)) {
		std::cout << "Error:\tThe username is invalide.\n";
		return 1;
	}

	std::string endpoint{ GetUserEventsEndpoint(username) };

	std::string json{ GitHubApiClient::SendGetRequest(endpoint) };

	auto events{ GitHubUserEventsParser::parse(json) };

	print(events);

	return 0;
}
