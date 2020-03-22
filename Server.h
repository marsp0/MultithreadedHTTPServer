#pragma once
#include <string>
#include <thread>
#include <vector>
#include "ListeningSocket.h"
#include "Queue.h"

class Server
{
	public:

		Server(std::string hostname, std::string port);
		~Server();
		void Start();
		void Stop();
		void Run();
		void HandleRequest();

	private:

		ListeningSocket				_socket;

		int							maxThreads;
		bool						stop;
		Queue						queue;
		std::vector<std::thread>	threadPool;
};

