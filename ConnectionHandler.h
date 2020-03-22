#pragma once
#include "Socket.h"

class ConnectionHandler
{
	public:
		ConnectionHandler();  // thius should take connection as argument
		~ConnectionHandler();
		void Handle(Socket* conn);

	private:


};

