#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <Common/Network/Connection/Connection.hpp>

namespace Nb::Network::Conn
{

Connection::Connection(int socketFd, sockaddr_in address) noexcept : socketFd(socketFd), address(address)
{
}

Connection::~Connection() noexcept
{
	if (socketFd >= 0)
	{
		::close(socketFd);
		socketFd = -1;
	}
}

} // namespace Nb::Network::Connection
