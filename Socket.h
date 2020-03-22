#pragma once
#include <WinSock2.h>
#include <string>

class Socket
{
	public:

		Socket(SOCKET sock);
		~Socket();
		void Send();
		void Receive();

	protected:

		SOCKET _socket;
		
};

