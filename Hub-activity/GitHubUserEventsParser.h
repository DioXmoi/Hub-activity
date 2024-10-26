#pragma once

#ifndef _1_12_26_10_2024_GITHUBUSEREVENTSPARSER_H_
#define _1_12_26_10_2024_GITHUBUSEREVENTSPARSER_H_


#include <algorithm>
#include <array>
#include <string>
#include <string_view>
#include <iostream>


namespace GitHub {
	namespace UserEventsParser {
		enum Type {
			CommitCommentEventType,
			CreateEventType,
			DeleteEventType,
			ForkEventType,
			GollumEventType,
			IssueCommentEventType,
			IssuesEventType,
			MemberEventType,
			PublicEventType,
			PullRequestEventType,
			PullRequestReviewEventType,
			PullRequestReviewCommentEventType,
			PullRequestReviewThreadEventType,
			PushEventType,
			ReleaseEventType,
			SponsorshipEventType,
			WatchEventType,
			MAX_TYPES,
		};

		struct Event {
			Type type{ };
			int count{ 0 };
		}; 

		using EventCollection = std::array<Event, Type::MAX_TYPES>;

		static constexpr EventCollection basicEvents{ Event{ CommitCommentEventType }, Event{ CreateEventType }, Event{ DeleteEventType }, Event{ ForkEventType },
				Event{ GollumEventType }, Event{ IssueCommentEventType }, Event{ IssuesEventType }, Event{ MemberEventType },
				Event{ PublicEventType }, Event{ PullRequestEventType }, Event{ PullRequestReviewEventType }, Event{ PullRequestReviewCommentEventType },
				Event{ PullRequestReviewThreadEventType }, Event{ PushEventType }, Event{ ReleaseEventType }, Event{ SponsorshipEventType }, Event{ WatchEventType } };

		static constexpr std::array eventsName{ "CommitCommentEvent", "CreateEvent", "DeleteEvent", "ForkEvent",
				"GollumEvent", "IssueCommentEvent", "IssuesEvent", "MemberEvent",
				"PublicEvent", "PullRequestEvent", "PullRequestReviewEvent", "PullRequestReviewCommentEvent",
				"PullRequestReviewThreadEvent", "PushEvent", "ReleaseEvent", "SponsorshipEvent", "WatchEvent" };

		std::ostream& operator<<(std::ostream& out, const Event& _event);

		void PrintEvent(const Event& _event);

		void Print(const EventCollection& events);

		EventCollection Parse(std::string_view json);
	}
}

#endif // !_1_12_26_10_2024_GITHUBUSEREVENTSPARSER_H_
