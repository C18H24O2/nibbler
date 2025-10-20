#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <Common/Network/Server/SocketServer.hpp>

static constexpr uint16_t DEFAULT_SERVER_PORT = 25565;

namespace Nb::GameServer
{
	int main(const int argc, char** argv)
	{
		auto port = argc > 1 ? std::stoi(argv[1]) : DEFAULT_SERVER_PORT;
		std::cout << "Starting game server on port " << port << "..." << std::endl;

		auto server = Network::Server::SocketServer::Create(port);
		if (!server)
		{
			std::cout << "Failed to start server: " << server.error() << std::endl;
			return (1);
		}

		while (server.RunEventLoop())
		{
			const auto result = server.AwaitEvent();

		}

		return (0);
	}

}

int main(const int argc, char** argv)
{
	try
	{
		return Nb::GameServer::main(argc, argv);
	}
	catch (const std::exception& e)
	{
		std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
