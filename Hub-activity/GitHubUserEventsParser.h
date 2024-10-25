#pragma once

#ifndef _1_12_26_10_2024_GITHUBUSEREVENTSPARSER_H_
#define _1_12_26_10_2024_GITHUBUSEREVENTSPARSER_H_


#include <algorithm>
#include <array>
#include <string>
#include <string_view>


struct Event {
	std::string type{ };
	int count{ 0 };
};

class GitHubUserEventsParser {
public:
	static std::array<Event, 17> parse(std::string_view json) {
		std::array events{ getBasicEvents() };

		std::size_t index{ 0 };
		while (index < json.size()) {
			index = json.find("type", index);
			if (index == std::string::npos) {
				break;
			}

			index += 7;
			std::string sub{ json.substr(index, json.find("\"", index) - index) };

			auto found{ std::ranges::find_if(events, [sub](const Event& event) -> bool { return event.type == sub; }) };
			if (found != events.end()) {
				found -> count += 1;
			}
		}

		return events;
	}

private:
	static std::array<Event, 17> getBasicEvents() {
		return std::array{ Event{ "CommitCommentEvent" }, Event{ "CreateEvent" }, Event{ "DeleteEvent" }, Event{ "ForkEvent" },
			Event{ "GollumEvent" }, Event{ "IssueCommentEvent" }, Event{ "IssuesEvent" }, Event{ "MemberEvent" },
			Event{ "PublicEvent" }, Event{ "PullRequestEvent" }, Event{ "PullRequestReviewEvent" }, Event{ "PullRequestReviewCommentEvent" },
			Event{ "PullRequestReviewThreadEvent" }, Event{ "PushEvent" }, Event{ "ReleaseEvent" }, Event{ "SponsorshipEvent" }, Event{ "WatchEvent" } };
	}
};


#endif // !_1_12_26_10_2024_GITHUBUSEREVENTSPARSER_H_
