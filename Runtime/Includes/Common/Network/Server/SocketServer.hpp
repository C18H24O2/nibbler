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
            explicit SocketServer(std::uint16_t port, std::int32_t fd);
            virtual ~SocketServer() noexcept;
            SocketServer(const SocketServer&) = delete;
            SocketServer& operator=(const SocketServer&) = delete;
            SocketServer(SocketServer&&) noexcept = default;
            SocketServer& operator=(SocketServer&&) noexcept = default;

            [[nodiscard]] std::optional<Conn::Connection> TryAccept() noexcept;
			void SetupSignalHandlers() noexcept;
            [[nodiscard]] bool RunEventLoop() const noexcept;
			void MarkForShutdown() noexcept;

            friend std::ostream& operator<<(std::ostream& os, const Error& error);

        public:
            static std::expected<SocketServer, Error> Create(std::uint16_t port) noexcept;

        private:
			friend class std::expected<SocketServer, Error>;

            std::uint16_t port;
            std::int32_t fd;
            bool running = true;

			std::vector<Conn::Connection> connections;
    };

};

#endif
