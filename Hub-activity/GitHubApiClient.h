#pragma once

#ifndef _15_39_21_10_2024_GITHUBAPICLIENT_H_
#define _15_39_21_10_2024_GITHUBAPICLIENT_H_


#include <Winsock2.h> 
#include <wininet.h>
#include <windows.h>
#include <stdexcept>
#include <string>
#include <string_view>



namespace GitHubApiClient {
	static std::string GetUserEventsEndpoint(const std::string& username) {
		return "/users/" + username + "/events";
	}

	static std::string SendGetRequest(const std::string& endpoint) {
		// Initialize WinInet
		HINTERNET hInternet = InternetOpenA("Hub-activity", 
			INTERNET_OPEN_TYPE_DIRECT, 
			NULL,
			NULL,
			0);

		if (hInternet == NULL) {
			throw std::runtime_error("Error:\tInternetOpen failed.\n");
		}

		// Open an HTTPS connection
		HINTERNET hConnect = InternetConnectA(hInternet,
			"api.github.com",
			INTERNET_DEFAULT_HTTPS_PORT,
			NULL,
			NULL,
			INTERNET_SERVICE_HTTP,
			0,
			NULL);

		if (hConnect == NULL) {
			InternetCloseHandle(hInternet);
			throw std::runtime_error("Error:\tInternetConnect failed.\n");
		}

		// Headers HTTPS request
		std::string headers = "Host: api.github.com\r\nAccept: application/vnd.github+json\r\nUser-Agent: Hub-activity\r\nConnection: close\r\n\r\n";

		// Building https request
		HINTERNET hRequest = HttpOpenRequestA(hConnect,
			"GET", 
			endpoint.c_str(), 
			"HTTP/1.1", 
			NULL, 
			NULL, 
			INTERNET_FLAG_SECURE, 
			0);

		// Send the request
		DWORD bytesSent{ static_cast<DWORD>(headers.size()) };
		BOOL sendResult = HttpSendRequestA(hRequest,
			headers.c_str(), 
			bytesSent, 
			NULL, 
			0);

		// If the request has not gone away
		if (!sendResult) {
			// Close connections
			InternetCloseHandle(hRequest);
			InternetCloseHandle(hConnect);
			InternetCloseHandle(hInternet);
			throw std::runtime_error("Error:\tHttpSendRequest failed.\n");
		}

		// Receive the response
		DWORD bytesRead = 0;
		char buffer[1024];
		std::string response;
		while (true) {
			BOOL readResult = InternetReadFile(hRequest,
				buffer, 
				sizeof(buffer), 
				&bytesRead);

			if (!readResult || bytesRead == 0) {
				break; // End of response or error
			}
			response.append(buffer, bytesRead);
		}

		// Close connections
		InternetCloseHandle(hRequest);
		InternetCloseHandle(hConnect);
		InternetCloseHandle(hInternet);

		return response;
	}

};

#endif // !_15_39_21_10_2024_GITHUBAPICLIENT_H_
