#ifndef NIBBLER_SERVER_SOCKETSERVER_HPP
#define NIBBLER_SERVER_SOCKETSERVER_HPP

#include <cstdint>
#include <expected>

#include <Common/Network/Connection/Connection.hpp>
#include <Common/Network/Server/SocketServer.hpp>

namespace Nb::Network::Server
{
    class SocketServer
    {
        public:
            enum class Error
            {
                CreateFailed,
                BindFailed,
                ListenFailed,
                AcceptFailed,
            };

        public:
            virtual ~SocketServer() noexcept;
            SocketServer(const SocketServer&) = delete;
            SocketServer& operator=(const SocketServer&) = delete;
            SocketServer(SocketServer&&) noexcept = default;
            SocketServer& operator=(SocketServer&&) noexcept = default;

            [[nodiscard]] bool RunEventLoop() const noexcept;
            [[nodiscard]] std::optional<Connection::Connection> TryAccept() noexcept;

            friend std::ostream& operator<<(std::ostream& os, const Error& error);

        public:
            static std::expected<SocketServer, Error> Create(std::uint16_t port) noexcept;

        private:
            explicit SocketServer(std::uint16_t port);

            std::uint16_t port;
            std::int32_t fd;
            bool running = true;
    };

};

#endif