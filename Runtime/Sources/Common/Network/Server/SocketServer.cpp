#include <Common/Network/Server/SocketServer.hpp>

#include <functional>
#include <mutex>
#include <unordered_map>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <signal.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

namespace Nb::Network::Server
{
	static struct {
		std::mutex mutex;
		std::unordered_map<int, std::function<void(int)>> handlers;
	}	SignalHandlers; // this is awful and i can't be bothered to make it half decent

	SocketServer::SocketServer(std::uint16_t port, std::int32_t fd) : port(port), fd(fd)
	{
	}

	SocketServer::~SocketServer() noexcept
	{
		if (fd >= 0)
		{
			std::cout << "Closing socket" << std::endl;
			::close(fd);
			fd = -1;
		}
	}

	bool SocketServer::RunEventLoop() const noexcept
	{
		return this->running;
	}

	std::optional<Conn::Connection> SocketServer::TryAccept() noexcept
	{
		sockaddr_in client_addr{};
		socklen_t client_len = sizeof(client_addr);
		
		int client_fd = ::accept(fd, reinterpret_cast<sockaddr*>(&client_addr), &client_len);
		int e = errno;
		if (client_fd < 0)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				return std::nullopt;

			//TODO: log error
			std::cout << "Failed to accept connection: " << std::strerror(e) << std::endl;
			return std::nullopt;
		}

		std::cout << "Accepted connection: " << client_fd << " " << std::strerror(e) << std::endl;
		
		return Conn::Connection(client_fd, client_addr);
	}

	void SocketServer::MarkForShutdown() noexcept
	{
		this->running = false;
	}

	std::expected<SocketServer, SocketServer::Error> SocketServer::Create(std::uint16_t port) noexcept
	{
		int fd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
		if (fd < 0)
		{
			return std::unexpected(Error::CreateFailed);
		}

		sockaddr_in addr{};
		std::memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = INADDR_ANY;
		addr.sin_port = htons(port);

		if (::bind(fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0)
		{
			close(fd);
			return std::unexpected(Error::BindFailed);
		}

		if (::listen(fd, 10) < 0)
		{
			close(fd);
			return std::unexpected(Error::ListenFailed);
		}

		int i = 1;
		::setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));

		return std::expected<SocketServer, SocketServer::Error>(std::in_place, port, fd);
	}

	static void SignalHandler(int signal)
	{
		SignalHandlers.handlers.at(signal)(signal);
	}

	void SocketServer::SetupSignalHandlers() noexcept
	{
		std::lock_guard lock(SignalHandlers.mutex);

		SignalHandlers.handlers[SIGINT] = [this](int signal) { this->MarkForShutdown(); };
		SignalHandlers.handlers[SIGTERM] = [this](int signal) { this->MarkForShutdown(); };

		::signal(SIGINT, SignalHandler);
		::signal(SIGTERM, SignalHandler);
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
