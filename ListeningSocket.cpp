#include "ListeningSocket.h"
#include <iostream>
#include <Ws2tcpip.h>

ListeningSocket::ListeningSocket(std::string hostname, std::string port) : Socket(INVALID_SOCKET), hostname(hostname), port(port)
{
    // Initializes windows socket stuff
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "WSAStartup failed." << std::endl;
        exit(1);
    }

    struct addrinfo hints;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
    //documentation dictates that these should be NULL 
    hints.ai_addrlen = NULL;
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    int success = getaddrinfo(this->hostname.c_str(), this->port.c_str(), &hints, &(this->socketInfo));

    if (success != 0)
    {
        std::cerr << "getaddrinfo failed: " << success << std::endl;
        WSACleanup();
        exit(1);
    }

    // create the socket - https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket
    this->_socket = socket(this->socketInfo->ai_family, this->socketInfo->ai_socktype, this->socketInfo->ai_protocol);
    if (this->_socket == INVALID_SOCKET)
    {
        std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
        freeaddrinfo(this->socketInfo);
        WSACleanup();
        exit(1);
    }
}

void ListeningSocket::Start()
{
    // bind documentation - https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-bind
    int bindSuccess = bind(this->_socket, this->socketInfo->ai_addr, this->socketInfo->ai_addrlen);
    if (bindSuccess != 0)
    {
        std::cerr << "Error at bind(): " << WSAGetLastError() << std::endl;
        freeaddrinfo(this->socketInfo);
        WSACleanup();
        exit(1);
    }

    if (listen(this->_socket, SOMAXCONN) == SOCKET_ERROR)
    {
        std::cerr << "Listen failed with error : " << WSAGetLastError() << std::endl;
        closesocket(this->_socket);
        WSACleanup();
        exit(1);
    }
}

std::unique_ptr<Socket> ListeningSocket::Accept()
{
    SOCKET newSocket = accept(this->_socket, NULL, NULL);
    if (newSocket == INVALID_SOCKET)
    {
        std::cerr << "Accept failed : " << WSAGetLastError() << std::endl;
        closesocket(this->_socket);
        WSACleanup();
        exit(1);
    }
    return std::make_unique<Socket>(newSocket);
}