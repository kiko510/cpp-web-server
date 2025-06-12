#include "Server.hpp"
#include <winsock2.h>
 #include <ws2tcpip.h>
#include <iostream>

Server::Server(const int port, const std::string &root) :
	m_port(port),
	m_root(root)
{

}

Server::~Server()
{
	stop();
}

void Server::run()
{
	//Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed.\n";
        return;
    }

    //Create socket
    m_listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_listen_socket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed.\n";
        WSACleanup();
        return;
    }

    // Bind
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(m_port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(m_listen_socket, (SOCKADDR*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed.\n";
        closesocket(m_listen_socket);
        WSACleanup();
        return;
    }

    // Listen
    if (listen(m_listen_socket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed.\n";
        closesocket(m_listen_socket);
        WSACleanup();
        return;
    }

    std::cout << "Server running on port " << m_port << "\n";

    // 5. Accept loop
	mainLoop();

}

void Server::stop()
{
	closesocket(m_listen_socket);
    WSACleanup();
}

void Server::mainLoop()
{
	 while (true) {
        SOCKET client_socket = accept(m_listen_socket, nullptr, nullptr);
        if (client_socket == INVALID_SOCKET) {
            std::cerr << "Accept failed.\n";
            continue;
        }

        // Read request
        char buffer[4096];
        int received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (received <= 0) {
            closesocket(client_socket);
            continue;
        }
        buffer[received] = '\0';
        std::string request(buffer);

		std::cout << "Message from client: " << request << std::endl;


        closesocket(client_socket);
    }
}
