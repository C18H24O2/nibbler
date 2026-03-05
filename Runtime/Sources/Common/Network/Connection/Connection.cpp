#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <unistd.h>

#include <Common/Network/Connection/Connection.hpp>

namespace Nb::Network::Conn
{

using Error = Connection::Error;

Connection::Connection(int socketFd, sockaddr_in address) noexcept : socketFd(socketFd), address(address)
{
}

std::expected<void, Error> Connection::SetTcpNoDelay(bool enabled) noexcept
{
	int value = enabled ? 1 : 0;
	if (::setsockopt(socketFd, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value)) < 0)
	{
		return std::unexpected(Error::SetSocketOptionFailed);
	}

	return {};
}

std::string Connection::GetRemoteIp() const noexcept
{
	char ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &address.sin_addr, ip, INET_ADDRSTRLEN);
	return std::string(ip);
}

std::uint16_t Connection::GetRemotePort() const noexcept
{
	return ntohs(address.sin_port);
}

int Connection::GetFd() const noexcept
{
	return socketFd;
}

Connection::~Connection() noexcept
{
	if (socketFd >= 0)
	{
		std::cout << "Closing connection socket: " << socketFd << std::endl;
		::close(socketFd);
		socketFd = -1;
	}
}

} // namespace Nb::Network::Connection
