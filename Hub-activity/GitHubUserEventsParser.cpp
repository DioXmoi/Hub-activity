#include "GitHubUserEventsParser.h"


void GitHub::UserEventsParser::PrintEvent(const Event& _event) {
	switch (_event.type) {
	case Type::CommitCommentEventType:
		std::cout << _event.count << " - commit comments were created.\n";
		break;
	case Type::CreateEventType:
		std::cout << _event.count << " - git branches or tags created.\n";
		break;
	case Type::DeleteEventType:
		std::cout << _event.count << " - git branches or tags were deleted.\n";
		break;
	case Type::ForkEventType:
		std::cout << _event.count << " - repositories were forked.\n";
		break;
	case Type::GollumEventType:
		std::cout << _event.count << " - wiki pages were created or updated.\n";
		break;
	case Type::IssueCommentEventType:
		std::cout << _event.count << " - issue or pull request comments were made.\n";
		break;
	case Type::IssuesEventType:
		std::cout << _event.count << " - issues were created or updated.\n";
		break;
	case Type::MemberEventType:
		std::cout << _event.count << " - collaborators were added to the repository.\n";
		break;
	case Type::PublicEventType:
		std::cout << _event.count << " - epositories were made public.\n";
		break;
	case Type::PullRequestEventType:
		std::cout << _event.count << " - pull requests were created.\n";
		break;
	case Type::PullRequestReviewEventType:
		std::cout << _event.count << " - pull request reviews were submitted.\n";
		break;
	case Type::PullRequestReviewCommentEventType:
		std::cout << _event.count << " - comments were added to the pull request’s unified diff.\n";
		break;
	case Type::PullRequestReviewThreadEventType:
		std::cout << _event.count << " - pull request comment threads were marked resolved.\n";
		break;
	case Type::PushEventType:
		std::cout << _event.count << " - commits were pushed to a repository branch or tag.\n";
		break;
	case Type::ReleaseEventType:
		std::cout << _event.count << " - releases were created.\n";
		break;
	case Type::SponsorshipEventType:
		std::cout << _event.count << " - sponsorship listings were created.\n";
		break;
	case Type::WatchEventType:
		std::cout << _event.count << " - repositories were starred.\n";
		break;
	}
}

void GitHub::UserEventsParser::Print(const EventCollection& events) {
	bool isEmpty{ true };
	for (const auto& _event : events) {
		if (_event.count > 0) {
			PrintEvent(_event);
			isEmpty = false;
		}
	}

	if (isEmpty) {
		std::cout << "You don't have any events.\n";
	}

	std::cout << '\n';
}

std::ostream& GitHub::UserEventsParser::operator<<(std::ostream& out, const Event& _event) {
	return out << eventsName[_event.type];
}

GitHub::UserEventsParser::EventCollection GitHub::UserEventsParser::Parse(std::string_view json) {
	std::array events{ basicEvents };

	std::size_t index{ 0 };
	while (index < json.size()) {
		index = json.find("type", index);
		if (index == std::string::npos) {
			break;
		}

		index += 7;
		std::size_t count{ json.find("\"", index) - index };
		std::string sub{ json.substr(index, count) };

		auto found{ std::ranges::find_if(events, [sub](const Event& _event) -> bool { 
			return eventsName[_event.type] == sub; 
			}) };

		if (found != events.end()) {
			found->count += 1;
		}
	}

	return events;
}