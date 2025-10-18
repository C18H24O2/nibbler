#include <Common/Network/SocketServer.hpp>

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

namespace Nb::Common::Network
{
	SocketServer::SocketServer(std::uint16_t port) : port(port), fd(-1)
	{
	}

	SocketServer::~SocketServer()
	{
		if (fd >= 0)
		{
			::close(fd);
			fd = -1;
		}
	}

	std::expected<SocketServer, SocketServer::Error> SocketServer::Create(std::uint16_t port) noexcept
	{
		auto server = SocketServer(port);

		server.fd = ::socket(AF_INET, SOCK_STREAM, 0);
		if (server.fd < 0)
		{
			return std::unexpected(Error::CreateFailed);
		}

		sockaddr_in addr{};
		std::memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = INADDR_ANY;
		addr.sin_port = htons(port);

		if (::bind(server.fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0)
		{
			return std::unexpected(Error::BindFailed);
		}

		if (::listen(server.fd, 10) < 0)
		{
			return std::unexpected(Error::ListenFailed);
		}

		int i = 1;
		::setsockopt(server.fd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));

		return std::move(server);
	}

	std::ostream& operator<<(std::ostream& os, const SocketServer::Error& error)
	{
		switch (error)
		{
			case SocketServer::Error::CreateFailed:
				os << "Socket creation failed";
				break;
			case SocketServer::Error::BindFailed:
				os << "Socket bind failed";
				break;
			case SocketServer::Error::ListenFailed:
				os << "Socket listen failed";
				break;
			case SocketServer::Error::AcceptFailed:
				os << "Socket accept failed";
				break;
			case SocketServer::Error::ReadFailed:
				os << "Socket read failed";
				break;
			case SocketServer::Error::WriteFailed:
				os << "Socket write failed";
				break;
			default:
				os << "Unknown error";
				break;
		}
		return os;
	}
}