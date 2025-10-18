#ifndef NIBBLER_COMMON_NETWORK_SOCKETSERVER_HPP
#define NIBBLER_COMMON_NETWORK_SOCKETSERVER_HPP

#include <cstdint>
#include <expected>
#include <ostream>

namespace Nb::Common::Network
{
    class SocketServer // : public NonCopyable
    {
        enum class Error
        {
            CreateFailed,
            BindFailed,
            ListenFailed,
            AcceptFailed,

            ReadFailed,
            WriteFailed
        };

        public:
            virtual ~SocketServer();

            static std::expected<SocketServer, Error> Create(std::uint16_t port) noexcept;

            friend std::ostream& operator<<(std::ostream& os, const Error& error);

        private:
            explicit SocketServer(std::uint16_t port);

            std::uint16_t port;
            std::int32_t fd;
    };

};

#endif // NIBBLER_COMMON_NETWORK_SOCKETSERVER_HPP