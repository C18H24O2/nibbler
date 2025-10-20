#include <Common/Network/Server/SocketServer.hpp>

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

namespace Nb::Network::Server
{
	SocketServer::SocketServer(std::uint16_t port) : port(port), fd(-1)
	{
	}

	SocketServer::~SocketServer() noexcept
	{
		if (fd >= 0)
		{
			::close(fd);
			fd = -1;
		}
	}

	bool SocketServer::RunEventLoop() const noexcept
	{
		return this->running;
	}

	std::optional<Connection::Connection> SocketServer::TryAccept() noexcept
	{
		return {};
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

	constexpr static std::string_view GetErrorString(const SocketServer::Error& error) noexcept
	{
		switch (error)
		{
			case SocketServer::Error::CreateFailed:
				return "Socket creation failed";
			case SocketServer::Error::BindFailed:
				return "Socket bind failed";
			case SocketServer::Error::ListenFailed:
				return "Socket listen failed";
			case SocketServer::Error::AcceptFailed:
				return "Socket accept failed";
			default:
				return "Unknown error";
		}
	}

	std::ostream& operator<<(std::ostream& os, const SocketServer::Error& error)
	{
		os << GetErrorString(error);
		return os;
	}
}