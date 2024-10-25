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

	std::string SendGetRequest(std::string_view endpoint) {
		SOCKET clientSocket{ CreateSocket() };

		addrinfo* info{ CreateAddrinfo(clientSocket, "api.github.com", "443") };

		Connect(clientSocket, info);

		std::string request{ GetHTTPRequest(endpoint) };

		Send(clientSocket, info, request);
		
		DWORD timeout = 30000; // Timeout in milliseconds (30 seconds)
		SetTimeout(clientSocket, info, timeout);

		std::string response{ ReadDataFromSocket(clientSocket, info) };

		closesocket(clientSocket);
		freeaddrinfo(info);

		return response;
	}

	SOCKET CreateSocket() {
		SOCKET clientSocket{ socket(AF_INET, SOCK_STREAM, 0) };
		if (clientSocket == INVALID_SOCKET) {
			closesocket(clientSocket);
			throw std::runtime_error{ "Error: Initialization socket # " + WSAGetLastError() + '.' + '\n' };
		}

		return clientSocket;
	}

	addrinfo* CreateAddrinfo(SOCKET clientSocket, std::string_view hostName, std::string_view serviceName) {
		addrinfo hints;
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		addrinfo* result = nullptr;
		if (getaddrinfo(hostName.data(), serviceName.data(), &hints, &result) != 0) { 
			closesocket(clientSocket);
			throw std::runtime_error{ "Error resolving hostname: " + WSAGetLastError() + '\n' };
		}

		return result;
	}

	void Connect(SOCKET clientSocket, addrinfo* info) {
		int isConnect{ connect(clientSocket, info -> ai_addr, (int)info -> ai_addrlen) };
		if (isConnect == SOCKET_ERROR) {
			closesocket(clientSocket);
			freeaddrinfo(info);
			throw std::runtime_error{ "Error connecting to server: " + WSAGetLastError() + '\n' };
		}
	}

	std::string GetHTTPRequest(std::string_view endpoint) {
		std::string request;

		request.append("GET ");
		request.append(endpoint.data());
		request.append(" HTTP/1.1\r\n");
		request.append("Host: api.github.com\r\n");
		request.append("Accept: application/vnd.github+json\r\n");
		request.append("User-Agent: Hub-activity\r\n");
		request.append("Connection: keep-alive\r\n\r\n");

		return request;
	}

	void Send(SOCKET clientSocket, addrinfo* info, std::string_view request) {
		int size{ static_cast<int>(request.size()) };
		int bytesSent = send(clientSocket, request.data(), size, 0);
		if (bytesSent == SOCKET_ERROR) {
			closesocket(clientSocket);
			freeaddrinfo(info);
			throw std::runtime_error{ "Error sending request: " + WSAGetLastError() + '\n' };
		}
	}

	void SetTimeout(SOCKET clientSocket, addrinfo* info, DWORD timeout) {
		int ans{ setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) };
		if (ans == SOCKET_ERROR) {
			closesocket(clientSocket);
			freeaddrinfo(info);
			throw std::runtime_error{ "Error setting receive timeout: " + WSAGetLastError() + '\n' };
		}
	}

	std::string ReadDataFromSocket(SOCKET clientSocket, addrinfo* info) {
		char buffer[1024];
		std::string response;
		int bytesReceived;
		while (true) {
			bytesReceived = recv(clientSocket, buffer, sizeof buffer, 0);
			if (bytesReceived == SOCKET_ERROR) {
				closesocket(clientSocket);
				freeaddrinfo(info);
				throw std::runtime_error{ "Error sending request: " + WSAGetLastError() + '\n' };
			}
			else if (bytesReceived == 0) {
				break;
			}
			else {
				response.append(buffer, bytesReceived);
			}
		}

		return response;
	}

private:

	WSADATA wsaData;
};

#endif // !_15_39_21_10_2024_GITHUBAPICLIENT_H_
