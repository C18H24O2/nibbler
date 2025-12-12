#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <netinet/in.h>
#include <signal.h>

#include <Common/Network/Server/SocketServer.hpp>

static constexpr uint16_t DEFAULT_SERVER_PORT = 25565;

using namespace std::chrono_literals;

namespace Nb::GameServer
{
	using namespace Network::Server;

	int main(const int argc, char** argv)
	{
		auto port = argc > 1 ? std::stoi(argv[1]) : DEFAULT_SERVER_PORT;
		std::cout << "Starting game server on port " << port << "..." << std::endl;

		auto server = SocketServer::Create(port);
		if (!server)
		{
			std::cout << "Failed to start server: " << server.error() << std::endl;
			return (1);
		}

		server->SetupSignalHandlers();
		std::cout << "Server started" << std::endl;
		while (server->RunEventLoop())
		{
			const auto target_time = std::chrono::steady_clock::now() + 50ms;

			const auto result = server->TryAccept();
			if (result)
			{
				std::cout << "New connection" << std::endl;
			}

			std::this_thread::sleep_until(target_time);
		}
		std::cout << "Server stopped" << std::endl;

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
