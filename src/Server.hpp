#ifndef __SERVER_H__
#define __SERVER_H__


#include <string>
#include <WinSock2.h>

class Server
{
	const int m_port;
	const std::string& m_root;
	SOCKET m_listen_socket;
public:
	Server(const int port, const std::string& root);
	~Server();

	void run();
	void stop();

private:
	void mainLoop();
};

#endif //__SERVER_H__