#include "GitHubApiClient.h"



std::string GitHub::ApiClient::SendGetRequest(const std::string& endpoint) {
	HINTERNET internet;
	HINTERNET connect;
	HINTERNET request;
	// Initialize WinInet
	internet = InternetOpenA("Hub-activity",
		INTERNET_OPEN_TYPE_DIRECT,
		NULL,
		NULL,
		0);

	if (internet == NULL) {
		throw std::runtime_error("Error:\tInternetOpen failed.\n");
	}

	// Open an HTTPS connection
	connect = InternetConnectA(internet,
		"api.github.com",
		INTERNET_DEFAULT_HTTPS_PORT,
		NULL,
		NULL,
		INTERNET_SERVICE_HTTP,
		0,
		NULL);

	if (connect == NULL) {
		InternetCloseHandle(internet);
		throw std::runtime_error("Error:\tInternetConnect failed.\n");
	}

	// Headers HTTPS request
	std::string headers = "Host: api.github.com\r\nAccept: application/vnd.github+json\r\nUser-Agent: Hub-activity\r\nConnection: close\r\n\r\n";

	// Building https request
	request = HttpOpenRequestA(connect,
		"GET",
		endpoint.c_str(),
		"HTTP/1.1",
		NULL,
		NULL,
		INTERNET_FLAG_SECURE,
		0);

	// Send the request
	DWORD bytesSent{ static_cast<DWORD>(headers.size()) };
	BOOL sendResult = HttpSendRequestA(request,
		headers.c_str(),
		bytesSent,
		NULL,
		0);

	// If the request has not gone away
	if (!sendResult) {
		// Close connections
		InternetCloseHandle(request);
		InternetCloseHandle(connect);
		InternetCloseHandle(internet);
		throw std::runtime_error("Error:\tHttpSendRequest failed.\n");
	}

	// Receive the response
	DWORD bytesRead = 0;
	char buffer[1024];
	std::string response;
	while (true) {
		BOOL readResult = InternetReadFile(request,
			buffer,
			sizeof(buffer),
			&bytesRead);

		if (!readResult || bytesRead == 0) {
			break; // End of response or error
		}
		response.append(buffer, bytesRead);
	}

	// Close connections
	InternetCloseHandle(request);
	InternetCloseHandle(connect);
	InternetCloseHandle(internet);

	return response;
}