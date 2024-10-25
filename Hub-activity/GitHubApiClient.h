#pragma once

#ifndef _15_39_21_10_2024_GITHUBAPICLIENT_H_
#define _15_39_21_10_2024_GITHUBAPICLIENT_H_

#include <Winsock2.h> 
#include <Ws2tcpip.h>
#include <stdexcept>
#include <stdio.h>    // For standard input/output
#include <string>
#include <string_view>

#include <iostream>



class GitHubApiClient {

public:

	GitHubApiClient() {
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
			throw std::runtime_error{ "Error: WinSock version initializaion #" + WSAGetLastError() + '.' + '\n'};
		}
	}

	~GitHubApiClient() {
		WSACleanup();
	}

	std::string SendGetRequest(const std::string& endpoint) {
		SOCKET serverSocket{ socket(AF_INET, SOCK_STREAM, 0) };
		if (serverSocket == INVALID_SOCKET) {
			closesocket(serverSocket);
			throw std::runtime_error{ "Error: Initialization socket # " + WSAGetLastError() + '.' + '\n' };
		}

		addrinfo hints;
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		addrinfo* result = nullptr;
		if (getaddrinfo("api.github.com", "80", &hints, &result) != 0) { // Port 443 for HTTPS
			closesocket(serverSocket);
			throw std::runtime_error{ "Error resolving hostname: " + WSAGetLastError() + '\n' };
		}

		int isConnect{ connect(serverSocket, result->ai_addr, (int)result->ai_addrlen) };
		if (isConnect == SOCKET_ERROR) {
			closesocket(serverSocket);
			freeaddrinfo(result);
			throw std::runtime_error{ "Error connecting to server: " + WSAGetLastError() + '\n' };
		}

		std::string request = "GET " +
			endpoint +
			" HTTP/1.1\r\n" +
			"Host: api.github.com\r\n" +
			"Accept: application/vnd.github+json\r\n" +
			"User-Agent: Hub-activity\r\n" +
			"Connection: keep-alive\r\n\r\n";

		int bytesSent = send(serverSocket, request.c_str(), static_cast<int>(request.size()), 0);
		if (bytesSent == SOCKET_ERROR) {
			closesocket(serverSocket);
			freeaddrinfo(result);
			throw std::runtime_error{ "Error sending request: " + WSAGetLastError() + '\n' };
		}

		DWORD timeout = 30000; // Timeout in milliseconds (30 seconds)
		int ans{ setsockopt(serverSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) };
		if (ans == SOCKET_ERROR) {
			closesocket(serverSocket);
			freeaddrinfo(result);
			throw std::runtime_error{ "Error setting receive timeout: " + WSAGetLastError() + '\n' };
		}

		char buffer[1024];
		std::string response;
		int bytesReceived;
		while (true) {
			bytesReceived = recv(serverSocket, buffer, sizeof buffer, 0);
			if (bytesReceived == SOCKET_ERROR) {
				closesocket(serverSocket);
				freeaddrinfo(result);
				throw std::runtime_error{ "Error sending request: " + WSAGetLastError() + '\n' };
			}
			else if (bytesReceived == 0) {
				std::cout << "Connection closed by server.\n";
				break;
			}
			else {
				response.append(buffer, bytesReceived);
			}
		}

		closesocket(serverSocket);
		freeaddrinfo(result);

		return response;
	}

private:

	WSADATA wsaData;
};

#endif // !_15_39_21_10_2024_GITHUBAPICLIENT_H_
