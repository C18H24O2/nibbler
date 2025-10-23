#ifndef NIBBLER_SERVER_CONNECTION_HPP
#define NIBBLER_SERVER_CONNECTION_HPP

#include <chrono>
#include <expected>
#include <tuple>

#include <Common/Utils/NonCopyable.hpp>
#include <netinet/in.h>

namespace Nb::Network::Connection
{
	template<typename T>
	concept Packet = requires(T t)
	{
		t.Fields();
		requires requires { 
			std::apply([](auto&&...) {}, t.fields()); 
		};
	};

	class Connection : Utils::NonCopyable
	{
		public:
			enum class Error {
				CreateFailed,
				ConnectFailed,
				ReadFailed,
				WriteFailed,
				ConnectionClosed,
				Timeout,
				WouldBlock,
				SetSocketOptionFailed,
				InvalidAddress
			};

		public:
			~Connection() noexcept override;

			[[nodiscard]] std::expected<std::size_t, Error> Read(std::span<std::byte> buffer) noexcept;
			[[nodiscard]] std::expected<std::size_t, Error> Write(std::span<const std::byte> data) noexcept;
			[[nodiscard]] std::expected<void, Error> ReadExact(std::span<std::byte> buffer) noexcept;
			[[nodiscard]] std::expected<void, Error> WriteAll(std::span<const std::byte> data) noexcept;

			std::expected<void, Error> SetTcpNoDelay(bool enabled) noexcept;
			std::expected<void, Error> SetBlocking(bool blocking) noexcept;
			std::expected<void, Error> SetTimeout(std::chrono::milliseconds read_timeout,
												  std::chrono::milliseconds write_timeout) noexcept;

			[[nodiscard]] std::string GetRemoteIp() const noexcept;
			[[nodiscard]] std::uint16_t GetRemotePort() const noexcept;
			[[nodiscard]] bool IsConnected() const noexcept;

			void Shutdown(bool read = true, bool write = true) noexcept;
			[[nodiscard]] int GetFd() const noexcept;

		   	static std::expected<Connection, Error> Create(int socketFd) noexcept;

			friend std::ostream& operator<<(std::ostream& os, const Error& error);

			friend class SocketServer;
		private:
			explicit Connection(int socketFd, sockaddr_in address) noexcept;

			int socketFd;
			sockaddr_in address;
	};

}

#endif
