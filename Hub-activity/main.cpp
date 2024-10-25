#include "GitHubApiClient.h"

#include "UsernameValidator.h"

#include <array>
#include <iostream>
#include <string>


#pragma comment(lib, "Ws2_32.lib")

std::string GetUserEventsEndpoint(const std::string& username) {
	return "/users/" + username + "/events";
}

constexpr std::array eventsName{ "CommitCommentEvent", "CreateEvent", "DeleteEvent", "ForkEvent", "GollumEvent", "IssueCommentEvent", "IssuesEvent",
		"MemberEvent", "PublicEvent", "PullRequestEvent", "PullRequestReviewEvent", "PullRequestReviewCommentEvent", "PullRequestReviewThreadEvent",
		"PushEvent", "ReleaseEvent", "SponsorshipEvent", "WatchEvent" };

int main(int argc, char* argv[]) {
	if (argc == 1) {
		std::cout << "Error:\tThe username is missing.\n";
		return 1;
	}

	GitHubApiClient client{ };


	std::string username{ argv[1] };
	if (!UsernameValidator::IsValidUsername(username)) {
		std::cout << "Error:\tThe username is invalide.\n";
		return 1;
	}

	std::string endpoint{ GetUserEventsEndpoint(username) };


	std::cout << client.SendGetRequest(endpoint);

	return 0;
}
