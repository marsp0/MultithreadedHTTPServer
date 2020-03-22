#include "Server.h"
#include <iostream>


// TODO (Martin) : add logging


Server::Server(std::string hostname, std::string port) :    _socket(hostname, port), 
                                                            maxThreads(2), 
                                                            queue(),
                                                            stop(false)
{

}

Server::~Server()
{

}

void Server::Run()
{
    this->_socket.Start();
    while (!this->stop)
    {
        std::unique_ptr<Socket> newConnection = this->_socket.Accept();
        std::cout << "Received connection" << std::endl;
    }
}

void Server::Start()
{
    // create the thread pool here
    for (int i = 0; i < this->maxThreads; i++)
    {
        std::thread t(&Server::HandleRequest, this);
        this->threadPool.push_back(std::move(t));
    }
}

void Server::Stop()
{
    // join all threads here and exit
    
    for (int i = 0; i < this->threadPool.size(); i++)
    {
        this->threadPool[i].join();
    }
}

void Server::HandleRequest()
{
    // TODO (Martin) : currently all threads are active even if they just sit in a loop. 
    // Perhaps find a way to "wake up" only the needed ones.
    while (!this->stop)
    {
        std::unique_ptr<Job> job = this->queue.Get();
        if (job != nullptr)
        {
            // do the job here
        }
    }
}