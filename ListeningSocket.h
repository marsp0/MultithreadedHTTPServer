#pragma once
#include "Socket.h"
#include <memory>

class ListeningSocket : public Socket
{
	public:

		ListeningSocket(std::string hostname, std::string port);
		std::unique_ptr<Socket> Accept();
		void Start();

	private:

		addrinfo* socketInfo;
		std::string hostname;
		std::string port;
};

