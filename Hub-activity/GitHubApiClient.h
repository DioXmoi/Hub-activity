#pragma once

#ifndef _15_39_21_10_2024_GITHUBAPICLIENT_H_
#define _15_39_21_10_2024_GITHUBAPICLIENT_H_


#include <windows.h>
#include <wininet.h>
#include <stdexcept>
#include <string>


namespace GitHub {
	namespace ApiClient {
		inline std::string GetUserEventsEndpoint(const std::string& username) {
			return "/users/" + username + "/events";
		}

		std::string SendGetRequest(const std::string& endpoint);
	}
}

#endif // !_15_39_21_10_2024_GITHUBAPICLIENT_H_
